#!/bin/bash

#NOTE: Run the script everytime you change it, to load it into cmake cache
#NOTE: for vscode with cmake tools, you can configure the settings.json file with these cmake parameters

cd ..

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake \
    -DBUILD_ZYKLON_EXAMPLES=ON \  
    ..

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    make -j $(nproc)
elif [[ "$OSTYPE" == "darwin"* ]]; then
    make -j $(sysctl -n hw.ncpu)
elif [[ "$OSTYPE" == "cygwin" ]]; then
    make
elif [[ "$OSTYPE" == "msys" ]]; then
    make
elif [[ "$OSTYPE" == "win32" ]]; then
    echo "I'm not sure this can happen."
elif [[ "$OSTYPE" == "freebsd"* ]]; then
    make
else
    echo "My God."
fi


# TODO: if os is linux
    # 

# TODO: if os is macOS
    