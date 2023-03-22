import argparse
import os
import sys
import shutil


def full_path(path: str) -> str:
    return os.path.abspath(path)


parser = argparse.ArgumentParser(
    prog="automated-tester",
    description="""
    This program performs automated testing on arduino code executables.
    you pass in a folder containing folders which contain ino files and 
    an arduinoCodeTest executable.
    Then this program will compile the ino files and run the test executable on them.
    """
)

parser.add_argument("-i", "--input_folder", required=True, type=full_path, help="The folder containing folders which contain ino files",
                    nargs=1)
parser.add_argument("-b", "--bin_folder", required=True, type=full_path, help="""The folder containing the build binaries will be added to path and used to 
                                                                        find arduinoCodeTest executable""", nargs=1)
args = parser.parse_args()

bin_folder: str = args.bin_folder[0]
input_folder: str = args.input_folder[0]

if not os.path.isdir(bin_folder):
    print("binary folder does not exists", file=sys.stderr)
    exit(1)

if not os.path.isdir(input_folder):
    print("input folder does not exist", file=sys.stderr)
    exit(1)

os.environ["PATH"] += ":" + bin_folder
