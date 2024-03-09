#!/bin/bash

set -e

rm -rf build
mkdir build
pushd build
cmake ..
make
popd

pushd src/impl/ruby/lib/ext
./extconf.rb
make
popd

pushd build
./gol-test-c
./gol-test-cxx --show-progress
popd
pushd test/impl/ruby
rake
popd
