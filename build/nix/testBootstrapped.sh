#!/bin/bash

# This script builds the compiler and runs it on the test-cases to test compiler output
./buildBootstrapped.sh

echo ''
echo '************************'
echo 'Testing Current (compile test-cases with current)'
rm -rf ../../translated/test-cases/*
mkdir -p ../../translated/test-cases/resources
for testcase in `ls ../../test-cases/*.ad`; do
	casename=`basename $testcase .ad`
	../../target/bootstrapped/Program $testcase -o ../../translated/test-cases/$casename.cpp
done
../../target/bootstrapped/Program ../../test-cases/resources/Resources.ad -r ../../test-cases/resources/Hello.rsrc -r ../../test-cases/resources/World.rsrc -o ../../translated/test-cases/resources/Resources.cpp
