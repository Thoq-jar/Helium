#!/bin/bash

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

if ! command_exists meson; then
    echo "Meson is not installed. Please install Meson and try again."
    exit 1
fi

if ! command_exists wx-config; then
    echo "wxWidgets is not installed. Please install wxWidgets and try again."
    exit 1
fi

meson setup buildDir
meson compile -C buildDir -j $(nproc)
