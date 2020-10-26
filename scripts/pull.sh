#!/bin/bash

# I know that some are redundant but this is personal

cd ..
git submodule update --init --recursive

cd lib/spdlog
git checkout master

cd lib/imgui-cmake
git checkout cmake

cd ../..

cd lib/imgui-test
git checkout docking

cd ../..