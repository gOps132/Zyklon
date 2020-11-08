#!/bin/bash

cd ..
git submodule update --init --recursive

cd lib/spdlog
git checkout master

cd ../..

cd lib/imgui-cmake
git checkout cmake

cd ../..

cd lib/imgui-test
git checkout docking

cd ../..