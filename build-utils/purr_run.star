#!/bin/bash
### I AM AWARE THIS IS NOT STARLARK,
### I HAVE PLANS TO CONVERT THIS TO STARLARK IN THE FUTURE

# Run Purrooser
if [[ -d "buildDir" ]]; then
    meson compile -C buildDir
    ./buildDir/purrooser
else
    meson setup buildDir
    meson compile -C buildDir
    ./buildDir/purrooser
fi