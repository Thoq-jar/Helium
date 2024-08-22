#!/bin/bash
### I AM AWARE THIS IS NOT STARLARK,
### I HAVE PLANS TO CONVERT THIS TO STARLARK IN THE FUTURE

# Linux crosscompile
if [ -d "buildLinux" ]; then
    rm -rf buildLinux
fi

meson setup buildLinux --cross-file linux_cross.txt
cd buildLinux || exit
ninja
cd ..
