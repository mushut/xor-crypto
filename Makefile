all: xor-test.exe

xor-test.exe:
	g++ -std=c++11 -g -o xor-test.exe main.cpp

clean:
	rm xor-test.exe
