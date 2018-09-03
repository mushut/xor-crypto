#!/bin/bash

echo xor-crypto tester

make
# key is 8 bits and 10101010 in binary
./xor-test.exe input.txt output.txt 10101010
./xor-test.exe output.txt validate.txt 10101010
cmp --silent input.txt validate.txt
testoutput1=$?
if [ $testoutput1 -eq 0 ]
then
	echo Test 1 succeeded
else
	echo Test 1 failed
fi
rm output.txt validate.txt

# Do tests for keys shorter than 8 bits
./xor-test.exe input.txt output.txt 10101
./xor-test.exe output.txt validate.txt 10101
cmp --silent input.txt validate.txt
testoutput2=$?
if [ $testoutput2 -eq 0 ]
then
	echo Test 2 succeeded
else
	echo Test 2 failed
fi
rm output.txt validate.txt

# Do tests for keys longer than 8 bits
make clean
