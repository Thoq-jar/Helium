#!/bin/bash

if test -d "build"; then
    cd "build" 
else
    mkdir -p "build"
    cd "build"
fi

 cmake ..
make -j $(nproc)

exit 0