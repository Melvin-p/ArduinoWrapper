#!/bin/bash

<<"COMMENT"
options are
-o output dir i.e /foo/bar/temp/
-f input ino file i.e /for/bar/files/sample.ino

all options are required full normalised path is required
if there ae space in the path to this file or provided path this script will not work

assuming clang++, clang-format, ar, ardunio-cli exists on path

The following commands need to be run to setup up arduino-cli for first time use
arduino-cli config init
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install "Adafruit RGB LCD Shield Library"

assuming build outputs in build/Release/output folder
assuming inputted paths are normalized and valid
assuming output directory exists
assuming input file exists
assuming sed supports -E flag
COMMENT


while getopts 'o:f:' options 
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
        *)
        exit 1
        ;;
    esac
done


if [ -z "${OUT_DIR}" ] || [ -z "${IN_FILE}" ] ; then 
    exit 1;
fi

# get location of this script file
# supporting files for compliation are assumed to be in the same dir as script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# check ino file is compilable normally exit if not

arduino-cli compile --fqbn arduino:avr:uno "$IN_FILE"

if [ $? -ne 0 ]; then
    exit 167;
fi

# copy the file over and change the extension
# run clang format this will make string hacking to remove includes easier

filename=$(basename -- "$IN_FILE")
filename_noext="${filename%.*}"

cp "$IN_FILE" "$OUT_DIR/$filename_noext.cpp"

clang-format --files= "$OUT_DIR/$filename_noext.cpp" -i

if [ $? -ne 0 ]; then
    exit 168;
fi

#remove includes

cat "$OUT_DIR/$filename_noext.cpp" | sed -E "s@([\t ]*)(#[\t ]*include[\t ]+)([<][^\r\n\t\f\v]*[>]|[\"][^\r\n\t\f\v]*[\"])@\1@" > "$OUT_DIR/${filename_noext}_processed.cpp"

if [ $? -ne 0 ]; then
    exit 169;
fi

# build exectuable

c++ -DLINUX  -O3 -DNDEBUG -include "$SCRIPT_DIR/sample_private.hpp" -I "$SCRIPT_DIR/../../src/library/ArduinoWrapper/" -std=gnu++17 -o "$OUT_DIR/$filename_noext.o" -c "$OUT_DIR/${filename_noext}_processed.cpp" -D lcd_enabled

if [ $? -ne 0 ]; then
    exit 170;
fi

ar rcs "$OUT_DIR/$filename_noext.a" "$OUT_DIR/$filename_noext.o"

if [ $? -ne 0 ]; then
    exit 171;
fi

c++ -DLINUX  -O3 -DNDEBUG -std=gnu++17 -o "$OUT_DIR/main.cpp.o" -c "$SCRIPT_DIR/main.cpp"

if [ $? -ne 0 ]; then
    exit 172;
fi

c++ -o "$OUT_DIR/$filename_noext.out" "$OUT_DIR/main.cpp.o" -l:"$filename_noext.a" -l:"libArduinoWrapper.so" -L"$SCRIPT_DIR/../../build/Release/output/" -L"$OUT_DIR"

if [ $? -ne 0 ]; then
    exit 173;
fi

# run file after appending to library path
#LD_APPEND=$(realpath $SCRIPT_DIR/../../build/Release/output/)
#export LD_LIBRARY_PATH=$LD_APPEND:$LD_LIBRARY_PATH
#$OUT_DIR/$filename_noext.out