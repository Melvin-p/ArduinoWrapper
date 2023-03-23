#!/bin/python

"""
arduino-cli is assumed to be on path
"""

import argparse
import os
import sys
import platform
import subprocess
import glob
import uuid
from concurrent.futures.thread import ThreadPoolExecutor
import time
import signal

if platform.system() != "Linux":
    print("Linux not detected", file=sys.stderr)
    exit(1)

# make porting in the future easier
path_sep: str = os.pathsep
sep: str = os.sep
adwr_name: str = "libArduinoWrapper.so"
arduino_test_name: str = "arduinoCodeTest"
this_path: str = os.path.abspath(os.path.dirname(__file__))
compile_script_path: str = this_path + sep + "arduinoCodeCompiler" + sep + "compile.sh"


def full_path(path: str) -> str:
    return os.path.abspath(path)


parser = argparse.ArgumentParser(
    prog="automated-tester",
    description="""
    This program performs automated testing on arduino code executables.
    you pass in a folder containing folders which contain ino files and 
    an arduinoCodeTest executable.
    Then this program will compile the ino files and run the test executable on them.
    you will need arduino-cli on your path
    """
)

parser.add_argument("-i", "--input_folder", required=True, type=full_path,
                    help="The folder containing folders which contain ino files",
                    nargs=1)

parser.add_argument("-b", "--bin_folder", required=True, type=full_path, help="""The folder containing the build 
binaries will be added to path and used to find arduinoCodeTest executable""", nargs=1)

parser.add_argument("-s", "--self_test", required=False, type=bool,
                    help="Run test to make sure everything is working correctly", default=True, nargs=1)

parser.add_argument("-t", "--threads", required=False, type=int,
                    help="Number of threads to use defaults to max core available", default=os.cpu_count(), nargs=1)

args = parser.parse_args()

bin_dir: str = args.bin_folder[0]
input_dir: str = args.input_folder[0]
adwr_path: str = os.path.join(bin_dir, adwr_name)
testing_exe: str = os.path.join(bin_dir, arduino_test_name)
self_test: bool = args.self_test
threads: int = args.threads
if threads < 1:
    threads = 1

if not os.path.isdir(bin_dir):
    print("binary folder does not exists", file=sys.stderr)
    exit(1)

if not os.path.isdir(input_dir):
    print("input folder does not exist", file=sys.stderr)
    exit(1)

if not os.path.isfile(adwr_path):
    print("shared library not found", file=sys.stderr)
    exit(1)

if not os.path.isfile(testing_exe):
    print("ArduinoCodeTest executable not found", file=sys.stderr)
    exit(1)

try:
    subprocess.run(["arduino-cli", "version"])
except subprocess.CalledProcessError:
    print("arduino-cli not found", file=sys.stderr)
    exit(1)

os.environ["PATH"] += path_sep + bin_dir
if "LD_LIBRARY_PATH" in os.environ:
    os.environ["LD_LIBRARY_PATH"] += path_sep + bin_dir
else:
    os.environ["LD_LIBRARY_PATH"] = bin_dir

if self_test:
    adwr_test: str = os.path.join(bin_dir, "ArduinoWrapper-test")
    if not os.path.isfile(adwr_test):
        print("ArduinoWrapper-test executable not found skipping self test", file=sys.stderr)
    else:
        output: subprocess.CompletedProcess = subprocess.run(["ArduinoWrapper-test", "-m"], capture_output=False)
        if output.returncode != 0:
            print("Self Test failed", file=sys.stderr)
            exit(1)

print("checks successful")
print("Building job list")

ino_paths: list[str] = []
for item in os.listdir(input_dir):
    temp_dir: str = os.path.join(input_dir, item)
    if os.path.isdir(temp_dir):
        for file in glob.glob(temp_dir + sep + "*ino"):
            ino_paths.append(file)

uuids: list[str] = []
for i in ino_paths:
    uuids.append(str(uuid.uuid4()))

jobs: list[tuple[str, str]] = list(zip(ino_paths, uuids))


def compile_and_run(job: tuple[str, str]) -> tuple[bool, str]:
    work_dir: str = os.path.dirname(job[0]) + sep
    filename: str = os.path.basename(job[0])
    filename_noext: str = filename.replace(".ino", "")
    try:
        os.mkdir(work_dir + sep + "output")
    except FileExistsError:
        pass
    except FileNotFoundError:
        print("missing folder cannot continue", file=sys.stderr)
        return False, job[0]
    output_dir: str = os.path.join(work_dir, "output") + sep
    log = open(file=output_dir + "automated-testing.log", mode="a", encoding="utf-8", errors='ignore', newline="\n")
    script_out = subprocess.run(["bash", compile_script_path, "-f" + job[0], "-o" + output_dir], capture_output=False)
    match script_out.returncode:
        case 0:
            log.write("file compiles for arduino\n")
            log.write("file compiled for native\n")
        case 167:
            log.write("failed to compile ino for arduino\n")
        case 168:
            log.write("clang format failed\n")
        case 169:
            log.write("file preprocessing failed\n")
        case 170:
            log.write("processed file failed to compile\n")
        case _:
            log.write("a compile error occurred\n")
    if script_out.returncode == 0:
        arduinoCode = subprocess.Popen([output_dir + sep + filename_noext + ".out"],
                                       env=dict(os.environ, **{"ard_ipc": job[1]}))
        time.sleep(60)
        arduinoCode.send_signal(signal.SIGTERM)
        arduinoCode.wait()
    """ todo 
    run arduinoCodeTest
    run arduinoCode asynchronously 
    once test finishes kill arduinoCode
    """
    log.close()
    return True, job[0]


compile_and_run(jobs[1])

executor = ThreadPoolExecutor(max_workers=threads)
