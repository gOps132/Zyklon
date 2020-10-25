#!/bin/bash

cd ..
git submodule update --init --recursive

cd lib/imgui-cmake
git checkout cmake

cd ../..

cd lib/imgui-test
git checkout f8a643eb9ab8bc9669821c4944ca4b367f0968f2

cd ../..