#!/bin/bash

#NOTE: Run in ${CMAKE_SOURCE_DIR} or root project directory
#NOTE: Run the script everytime you change it, to load it into cmake cache
#NOTE: for vscode: you could also configure the settings.json file with these cmake parameters

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake \
    -DCMAKE_CXX_COMPILER="g++" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_SHARED_LIBS=ON \
    -DSPDLOG_ENABLE_PCH=ON \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    ..
make
cd ..
cd bin
cd Sandbox-Debug
./sandbox