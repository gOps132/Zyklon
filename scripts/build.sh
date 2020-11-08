#!/bin/bash

#NOTE: Run the script everytime you change it, to load it into cmake cache
#NOTE: for vscode with cmake tools, you can configure the settings.json file with these cmake parameters

cd ..

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake \
    
    ..

# TODO: if os is linux
    make -j $(nproc)

# TODO: if os is macOS
    # make -j $(sysctl -n hw.ncpu)