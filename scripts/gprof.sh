#!/bin/bash

cd .. 

if [ ! -d "benchmark" ]; then
    mkdir benchmark
fi

file=$(date +"%m_%d_%y_%H:%M:%S").txt

gprof ./bin/Sandbox-Debug/sandbox > $file

mv $file benchmark