#!/bin/bash

<<"COMMENT"
-o output directory i.e /foo/bar/temp/test.cpp
-i input cpp file i.e /for/bar/files/test.ino

The following commands need to be run to setup up arduino-cli for first time use
arduino-cli config init
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install "Adafruit RGB LCD Shield Library"

assuming output directory exists
assuming input file exists
assuming ardunio-cli is on path
assuming sed supports -E flag

COMMENT

while getopts 'o:i:' options 
do
    case $options in
        o)
        OUT_DIR=$OPTARG
        export OUT_DIR
        ;;
        i)
        IN_FILE=$OPTARG
        export IN_FILE
        ;;
        *)
        exit 1
        ;;
    esac
done


if [ -z "${OUT_DIR}" ] || [ -z "${IN_FILE}" ]; then 
    exit 1;
fi

# check ino file is compilable normally exit if not

arduino-cli compile --fqbn arduino:avr:uno "$IN_FILE"

if [ $? -ne 0 ]; then
    exit 1;
fi

# copy the file over and change the extension
# run clang format this will make string hacking to remove includes easier

filename=$(basename -- "$IN_FILE")
filename_noext="${filename%.*}"

cp "$IN_FILE" "$OUT_DIR/$filename_noext.cpp"

clang-format --files= "$OUT_DIR/$filename_noext.cpp" -i

cat "$OUT_DIR/$filename_noext.cpp" | sed -E "s|^(#\s*include\s+[<\"]\S*[>\"])\s*((//.*)?(/\**.*)?)$|\2|g" > "$OUT_DIR/${filename_noext}_processed.cpp"
