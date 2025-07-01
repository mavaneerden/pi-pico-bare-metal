#!/bin/bash

if [[ $1 != "Debug" && $1 != "Release" && $1 != "RelWithDebInfo" && $1 != "MinSizeRel" ]]; then
    echo "First argument must be 'Debug', 'Release', 'RelWithDebInfo' or 'MinSizeRel'."
    exit
fi

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

rm -rf install
mkdir -p build

# Invoke CMake.
cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=$1 \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DTOOLCHAIN_BIN_PATH=$SCRIPT_DIR/../toolchain/bin/ \
    -DCMAKE_TOOLCHAIN_FILE=$SCRIPT_DIR/../cmake/toolchain.cmake \
    -DCMAKE_INSTALL_PREFIX:PATH=$SCRIPT_DIR/install

# Make all examples.
cmake --build build --target install --config $1 -j
