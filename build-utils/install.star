#!/bin/bash
### I AM AWARE THIS IS NOT STARLARK,
### I HAVE PLANS TO CONVERT THIS TO STARLARK IN THE FUTURE

# Install
if [[ -d "buildDir" ]]; then
    meson compile -C buildDir
else
    meson setup buildDir
    meson compile -C buildDir
fi
sh build-utils/postinstall.star
