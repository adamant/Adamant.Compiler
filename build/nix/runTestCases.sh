#!/bin/bash

# This script builds and runs the test cases expected values
./buildTestCases.sh

for testcase in `ls ../../target/test-cases/*`; do
	echo Testing `basename $testcase`
	$testcase
	echo "Exit Code is $?"
done
