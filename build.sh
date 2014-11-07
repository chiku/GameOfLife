#!/bin/bash

set -e

rm -rf build
mkdir build
pushd build
cmake ..
make

./gol-test-c
./gol-test-cxx --show-progress

popd
pushd src/impl/ruby/lib/ext
./extconf.rb
make
popd
cd test/impl/ruby
rake
