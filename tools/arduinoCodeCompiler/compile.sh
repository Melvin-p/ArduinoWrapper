#!/bin/bash

<<"COMMENT"
options are
-o output dir i.e /foo/bar/temp/
-f input cpp file i.e /for/bar/files/sample.cpp
-p name of output executable i.e. sample

all options are required full normalised path is required
if there ae space in the path to this file or provided path this script will not work

no sanity checks performed
assuming g++, ar exists
assuming build outputs in build/Release/output folder
assuming inputted paths are normalized and valid
COMMENT


while getopts 'o:f:p:' options 
do
    case $options in
        o)
        OUT_DIR=$OPTARG
        export OUT_DIR
        ;;
        f)
        IN_FILE=$OPTARG
        export IN_FILE
        ;;
        p)
        OUT_NAME=$OPTARG
        export OUT_NAME
        ;;
        *)
        exit 1
        ;;
    esac
done


if [ -z "${OUT_DIR}" ] || [ -z "${IN_FILE}" ] || [ -z "${OUT_NAME}" ]; then 
    exit 1;
fi

# get location of this script file
# supporting files for compliation are assumed to be in the same dir as script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# build exectuable

g++ -DLINUX  -O3 -DNDEBUG -include "$SCRIPT_DIR/sample_private.hpp" -I "$SCRIPT_DIR/../../src/library/ArduinoWrapper/" -std=gnu++17 -o "$OUT_DIR/$OUT_NAME.o" -c "$IN_FILE"

if [ $? -ne 0 ]; then
    exit 1;
fi

ar rcs "$OUT_DIR/$OUT_NAME.a" "$OUT_DIR/$OUT_NAME.o"

if [ $? -ne 0 ]; then
    exit 1;
fi

g++ -DLINUX  -O3 -DNDEBUG -std=gnu++17 -o "$OUT_DIR/main.cpp.o" -c "$SCRIPT_DIR/main.cpp"

if [ $? -ne 0 ]; then
    exit 1;
fi

g++ -o  "$OUT_DIR/$OUT_NAME.out" "$OUT_DIR/main.cpp.o" -l:"$OUT_NAME.a" -l:"libArduinoWrapper.so" -L"$SCRIPT_DIR/../../build/Release/output/" -L"$OUT_DIR"

if [ $? -ne 0 ]; then
    exit 1;
fi

# run file after appending to library path
# LD_APPEND=$(realpath $SCRIPT_DIR/../../build/Release/output/)
# export LD_LIBRARY_PATH=$LD_APPEND:$LD_LIBRARY_PATH
# $OUT_DIR/$OUT_NAME.out