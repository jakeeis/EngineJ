#!/bin/bash

readonly MAKEFILE="./Makefile"
readonly SRC_PATH="./src"
readonly INCLUDE_PATH="./include"
readonly HEADER_PATH="./include/headers"
readonly LIB_PATH="./libs"
readonly BUILD_PATH="./build"

readonly CC="emcc"
readonly CFLAGS="-Wall -Wextra -std=c++20 -fwasm-exceptions"
readonly EMFLAGS="-sALLOW_MEMORY_GROWTH=1 -sFULL_ES2=1 -sWASM=1 -sNO_EXIT_RUNTIME=1 --embed-file assets"
readonly TARGET="./build/engine.js"

headerDirs=$(find "$INCLUDE_PATH"/* -type d)

includeStr=""
for headerDir in ${headerDirs}
do
  includeStr+="-I$headerDir "
done

printf "" > "$MAKEFILE"

printf "CC := $CC\n" >> "$MAKEFILE"
printf "CFLAGS := $CFLAGS\n" >> "$MAKEFILE"
printf "EMFLAGS := $EMFLAGS\n" >> "$MAKEFILE"
printf "TARGET := $TARGET\n\n" >> "$MAKEFILE"

libFiles=$(find "$LIB_PATH" -type f -name "*.a")
printf "LIBS := $libFiles\n" >> "$MAKEFILE"
printf "HEADERS := $includeStr\n" >> "$MAKEFILE"
printf "CFLAGS_INCLUDE := \$(CFLAGS) \$(HEADERS)\n\n" >> "$MAKEFILE"
	
printf ".PHONY: all clean\n\n" >> "$MAKEFILE"

printf "all: \$(TARGET)\n\n" >> "$MAKEFILE"

printf "clean:\n" >> "$MAKEFILE"
printf "\t@rm -rf ./build/*\n\n" >> "$MAKEFILE"

srcFiles=$(find "$SRC_PATH" -type f \( -name "*.c" -o -name "*.cpp" \))

objs=""

for srcFile in ${srcFiles}; do
    # echo $srcFile
    headerFileNames=$(grep -oP "(?<=#include \").*?(?=\")" "$srcFile")

    x="${srcFile/$SRC_PATH/$BUILD_PATH}"
    objFile="${x/cpp/o}"

    deps=""
    for headerFileName in ${headerFileNames}; do
        headerFile=$(find "$INCLUDE_PATH" -type f -name "*$headerFileName")
        deps+="$headerFile "

        depSrcFileName="${headerFileName/hpp/cpp}"
        depSrcFile=$(find "$SRC_PATH" -type f -name "*$depSrcFileName")
        deps+="$depSrcFile "
    done
    # echo $deps

    compileStr="\$(CC) \$(CFLAGS_INCLUDE) -c $srcFile -o $objFile"

    printf "$objFile: $srcFile ${deps/$'\n'/" "}\n" >> "$MAKEFILE"
    printf "\t@mkdir -p $(dirname $objFile)\n" >> "$MAKEFILE"
    printf "\t$compileStr\n\n" >> "$MAKEFILE"

    objs+="$objFile "

    # echo
done

printf "\$(TARGET): $objs\n" >> "$MAKEFILE"
printf "\t\$(CC) \$(CFLAGS_INCLUDE) \$(EMFLAGS) $^ -o \$@\n" >> "$MAKEFILE"
