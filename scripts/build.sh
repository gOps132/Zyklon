#!/bin/bash

#NOTE: Run the script everytime you change it, to load it into cmake cache
#NOTE: for vscode: you need configure the settings.json file with these cmake parameters

cd ..

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake \
    -DCMAKE_CXX_COMPILER="g++" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    ..
    
make -j $(nproc)

cd ..

./bin/Sandbox-Debug/sandbox