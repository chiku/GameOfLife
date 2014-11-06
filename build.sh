#!/bin/bash

rm -rf build
mkdir build
pushd build
cmake ..
make

./gol-test-c
./gol-test-cxx --show-progress

popd
pushd src/ports/ruby/lib/ext
./extconf.rb
make
popd
cd test/ports/ruby
rake
