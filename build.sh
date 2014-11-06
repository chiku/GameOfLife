#!/bin/bash

rm -rf build
mkdir build
cd build
cmake ..
make
./gol-test-c
./gol-test-cxx
