#!/bin/bash

#NOTE: Run the script everytime you change it, to load it into cmake cache
#NOTE: for vscode: you need configure the settings.json file with these cmake parameters

cd ..

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    ..

# TODO: if os is linux
    make -j $(nproc)
# TODO: if os is macOS
    # make -j $(sysctl -n hw.ncpu)

cd ..

./bin/Sandbox-Debug/sandbox

# There seems to be some issues with the g++-10 compiler with macOS, likely
# because this kind architecture or kernel is not supported, I have to specify
# a special executable from gcc for the darwin kernel "x86_64-apple-darwin18-g++-10"
# apparently that does not work also.