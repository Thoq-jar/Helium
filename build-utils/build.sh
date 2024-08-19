#!/bin/bash

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

if ! command_exists cmake; then
    echo "CMake is not installed. Please install CMake and try again."
    exit 1
fi

if ! command_exists wx-config; then
    echo "wxWidgets is not installed. Please install wxWidgets and try again."
    exit 1
fi

mkdir -p cmake-build-minsizerel
# shellcheck disable=SC2164
cd cmake-build-minsizerel

cmake ..
# shellcheck disable=SC2046
cmake --build . --target Purrooser -j $(nproc)