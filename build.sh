#!/bin/bash

if [[ $1 != "debug" && $1 != "release" ]]; then
    echo "First argument must be 'debug' or 'release'."
    exit
fi

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

rm -rf install
mkdir -p build

# Invoke CMake.
cmake -S . -B build/$1 --preset $1

# Make all examples.
cmake --build build/$1 --target install -j
