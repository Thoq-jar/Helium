#!/bin/bash

export CC="/opt/homebrew/bin/x86_64-w64-mingw32-gcc"
export CXX="/opt/homebrew/bin/x86_64-w64-mingw32-g++"

if [ -d "build_windows" ]; then
    rm -rf build_windows
fi

mkdir build_windows

cd build_windows || exit

cmake .. -DCMAKE_TOOLCHAIN_FILE=../windows_toolchain.cmake

cmake --build .

cd ..
