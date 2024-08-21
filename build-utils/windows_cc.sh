#!/bin/bash

if [ -d "buildWindows" ]; then
    rm -rf buildWindows
fi

meson setup buildWindows --cross-file windows_cross.txt
cd buildWindows || exit
ninja
cd ..