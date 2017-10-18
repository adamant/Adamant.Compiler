#!/bin/bash

# This script builds the test-cases expected values to make sure they are valid C++
clear
echo 'Building all test cases'
mkdir -p ../../target/test-cases
rm -rf ../../target/test-cases/*
for testcase in `ls ../../test-cases/*.cpp`; do
	casename=`basename $testcase .cpp`
	echo $casename
	clang++ $testcase ../../src/RuntimeLibrary.cpp --include-directory ../../src -o ../../target/test-cases/$casename -std=c++14
done

clang++ ../../test-cases/resources/Resources.cpp ../../src/RuntimeLibrary.cpp --include-directory ../../src -o ../../target/test-cases/Resources -std=c++14
