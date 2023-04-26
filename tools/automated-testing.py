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
import logging

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
formatter = logging.Formatter('%(asctime)s | %(levelname)s | %(message)s')
formatter.converter = time.gmtime


def create_logger(name: str, log_file: str, level: int = logging.INFO) -> logging.Logger:
    """
    create a logger object with a log file
    :param name:
    :param log_file:
    :param level:
    :return:
    """
    handler: logging.FileHandler = logging.FileHandler(log_file)
    handler.setFormatter(formatter)
    logger: logging.Logger = logging.getLogger(name)
    logger.setLevel(level)
    logger.addHandler(handler)
    return logger


def destroy_logger(logger: logging.Logger) -> None:
    """
    Closes a logger object handles
    need to prevent resource leaks in threads
    :param logger:
    :return:
    """
    for handle in logger.handlers:
        logger.removeHandler(handle)
        handle.close()


def full_path(path: str) -> str:
    return os.path.abspath(path)


parser = argparse.ArgumentParser(
    prog="automated-tester",
    description="""
    This program performs automated testing on arduino sketches.
    Pass in a folder containing folders containing sketches and 
    the folder containing the built binaries.
    Then this program will compile the ino files and run the test executable on them.
    You will need arduino-cli on your path
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
parser.add_argument("-l", "--log_level", required=False, default=logging.INFO, nargs=1,
                    choices=[logging.DEBUG, logging.INFO, logging.WARNING, logging.ERROR, logging.CRITICAL], type=int)

args = parser.parse_args()

bin_dir: str = args.bin_folder[0]
input_dir: str = args.input_folder[0]
adwr_path: str = os.path.join(bin_dir, adwr_name)
testing_exe: str = os.path.join(bin_dir, arduino_test_name)
self_test: bool = args.self_test
threads: int = args.threads

log_level: int = 10
try:
    log_level = args.log_level[0]
except TypeError:
    log_level = args.log_level

if threads < 1:
    threads = 1

if not os.path.isdir(input_dir):
    print("input folder does not exist", file=sys.stderr)
    exit(1)

main_logger = create_logger("main_logger", os.path.join(input_dir, "log.log"), log_level)
main_logger.info("Begin automated testing")

if not os.path.isdir(bin_dir):
    print("binary folder does not exist", file=sys.stderr)
    main_logger.error("binary folder does not exist")
    exit(1)

if not os.path.isfile(adwr_path):
    print("ArduinoWrapper shared library does not exists", file=sys.stderr)
    main_logger.error("ArduinoWrapper shared library does not exists")
    exit(1)

if not os.path.isfile(testing_exe):
    print("ArduinoCodeTest executable not found", file=sys.stderr)
    main_logger.error("ArduinoCodeTest executable not found")
    exit(1)

try:
    subprocess.run(["arduino-cli", "version"], check=True)
except subprocess.CalledProcessError:
    print("arduino-cli not working", file=sys.stderr)
    main_logger.critical("arduino-cli not working")
    exit(1)
except FileNotFoundError:
    print("arduino-cli not found", file=sys.stderr)
    main_logger.critical("arduino-cli not found")
    exit(1)

try:
    subprocess.run(["clang-format", "--version"], check=True)
except subprocess.CalledProcessError:
    print("clang-format not working", file=sys.stderr)
    main_logger.critical("clang-format not working")
    exit(1)
except FileNotFoundError:
    print("clang-format not found", file=sys.stderr)
    main_logger.critical("clang-format not found")
    exit(1)

main_logger.debug("Threads: " + str(threads))
main_logger.debug("ArduinoCodeTest executable: " + testing_exe)
main_logger.debug("ArduinoWrapper shared library: " + adwr_path)
main_logger.debug("Input Folder: " + input_dir)
main_logger.debug("Binary Folder: " + bin_dir)
main_logger.debug("Self Test: " + str(self_test))

os.environ["PATH"] += path_sep + bin_dir
main_logger.info("appended to path")
if "LD_LIBRARY_PATH" in os.environ:
    os.environ["LD_LIBRARY_PATH"] += path_sep + bin_dir
    main_logger.info("appended to LD_LIBRARY_PATH")
else:
    os.environ["LD_LIBRARY_PATH"] = bin_dir
    main_logger.info("created LD_LIBRARY_PATH")

if self_test:
    adwr_test: str = os.path.join(bin_dir, "ArduinoWrapper-test")
    if not os.path.isfile(adwr_test):
        main_logger.warning("ArduinoWrapper-test executable not found skipping self test")
    else:
        awt_out: subprocess.CompletedProcess = subprocess.run(["ArduinoWrapper-test", "-m"], capture_output=True)
        if awt_out.returncode != 0:
            print("Self Test failed", file=sys.stderr)
            main_logger.critical("self test failed")
            exit(1)
        else:
            main_logger.info("self test succeed")

main_logger.info("checks successful")
main_logger.info("Building job list")

ino_paths: list[str] = []
for item in os.listdir(input_dir):
    temp_dir: str = os.path.join(input_dir, item)
    if os.path.isdir(temp_dir):
        for file in glob.glob(temp_dir + sep + "*ino"):
            ino_paths.append(file)

main_logger.info(str(len(ino_paths)) + " ino files founds")

uuids: list[str] = []
for i in ino_paths:
    uuids.append(str(uuid.uuid4()))

jobs: list[tuple[str, str]] = list(zip(ino_paths, uuids))
main_logger.info(str(len(jobs)) + " jobs created")


def worker(job: tuple[str, str]) -> tuple[bool, str]:
    work_dir: str = os.path.dirname(job[0]) + sep
    filename: str = os.path.basename(job[0])
    filename_noext: str = filename.replace(".ino", "")
    try:
        os.mkdir(work_dir + sep + "output")
    except FileExistsError:
        pass
    except FileNotFoundError:
        return False, job[0]
    output_dir: str = os.path.join(work_dir, "output") + sep
    log = create_logger(job[1], os.path.join(output_dir, "log.log"), log_level)
    log.info("Begin Test")
    log.info("UUID: " + job[1])
    log.debug("Work Directory: " + work_dir)
    log.debug("Ino File: " + filename)
    log.debug("Output Directory: " + output_dir)
    script_out = subprocess.run(["bash", compile_script_path, "-f" + job[0], "-o" + output_dir, "-b" + bin_dir], capture_output=True)
    match script_out.returncode:
        case 0:
            log.info("file compiles for arduino")
            log.info("file compiled for native")
        case 167:
            log.error("failed to compile ino for arduino")
        case 168:
            log.error("clang format failed")
        case 169:
            log.error("file preprocessing failed")
        case 170:
            log.error("processed file failed to compile")
        case _:
            log.error("a compile error occurred")
    if script_out.returncode == 0:
        arduinoCode = subprocess.Popen([output_dir + sep + filename_noext + ".out"],
                                       env=dict(os.environ, **{"ard_ipc": job[1]}), cwd=work_dir)
        arduinoTest = subprocess.run([testing_exe], env=dict(os.environ, **{"ard_ipc": job[1]}), cwd=work_dir,
                                     capture_output=True)
        arduinoCode.send_signal(signal.SIGTERM)
        ac_return: int = arduinoCode.wait()
        log.info("arduinoCode return code: " + str(ac_return))
        log.info("arduinoCodeTest return code: " + str(arduinoTest.returncode))
    else:
        destroy_logger(log)
        return False, job[0]
    destroy_logger(log)
    return True, job[0]


results: list[tuple[bool, str]] = []
executor = ThreadPoolExecutor(max_workers=threads)
for result in executor.map(worker, jobs):
    results.append(result)
