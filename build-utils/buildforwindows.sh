#!/bin/bash

if [ -d "buildWindows" ]; then
    rm -rf buildWindows
fi

meson setup buildWindows --cross-file cross_compile.txt
cd buildWindows || exit
ninja
cd ..