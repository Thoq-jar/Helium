#!/bin/bash

if [ -d "buildLinux" ]; then
    rm -rf buildLinux
fi

meson setup buildLinux --cross-file linux_cross.txt
cd buildLinux || exit
ninja
cd ..