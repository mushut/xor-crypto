#!/bin/bash

echo xor-crypto tester

# Does not work yet (need files and keys as arguments to work)
make
./xor-test.exe input.txt output.txt 10101010
./xor-test.exe output.txt validate.txt 10101010
# Check that input.txt is same as validate.txt
rm output.txt validate.txt
# Do tests for keys shorter than 8 bits
# Do tests for keys longer than 8 bits
make clean
