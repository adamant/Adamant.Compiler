#!/bin/bash

# This script builds the current version, then uses it on itself
./buildCurrent.sh

echo ''
echo '************************'
echo Building Bootstrapped
mkdir -p ../../translated/bootstrapped
rm -rf ../../translated/bootstrapped/*
source_files=`ls -d ../../src/*.ad ../../src/**/*.ad`
../../target/current/Program $source_files -o ../../translated/bootstrapped/Program.cpp -r ../../src/RuntimeLibrary.cpp -r ../../src/RuntimeLibrary.h
mkdir -p ../../target/bootstrapped
rm -rf ../../target/bootstrapped/*
clang++ ../../translated/bootstrapped/*.cpp -o ../../target/bootstrapped/Program -std=c++14
