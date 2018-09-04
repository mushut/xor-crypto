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
# 10010011
./xor-test.exe input.txt output.txt 10010011
./xor-test.exe output.txt validate.txt 10010011
cmp --silent input.txt validate.txt
testoutput2=$?
if [ $testoutput2 -eq 0 ]
then
	echo Test 2 succeded
else
	echo Test 2 failed
fi
rm output.txt validate.txt

# Do tests for keys shorter than 8 bits
./xor-test.exe input.txt output.txt 10101
./xor-test.exe output.txt validate.txt 10101
cmp --silent input.txt validate.txt
testoutput3=$?
if [ $testoutput3 -eq 0 ]
then
	echo Test 3 succeeded
else
	echo Test 3 failed
fi
rm output.txt validate.txt

# Do tests for keys longer than 8 bits
# 101010101
./xor-test.exe input.txt output.txt 101010101
./xor-test.exe output.txt validate.txt 101010101
cmp --silent input.txt validate.txt
testoutput4=$?
if [ $testoutput4 -eq 0 ]
then
	echo Test 4 succeeded
else
	echo Test 4 failed
fi
rm output.txt validate.txt
# 10011001101010100101010100001111 (32 bits)
./xor-test.exe input.txt output.txt 10011001101010100101010100001111
./xor-test.exe output.txt validate.txt 10011001101010100101010100001111
cmp --silent input.txt validate.txt
testoutput5=$?
if [ $testoutput5 -eq 0 ]
then
	echo Test 5 succeeded
else
	echo Test 5 failed
fi
rm output.txt validate.txt

make clean
