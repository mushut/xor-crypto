all: xor-test.exe

xor-test.exe: xor-test.o
	g++ -o xor-test.exe xor-test.o

xor-test.o: main.cpp
	g++ -c main.cpp

clean:
	rm xor-test.o xor-test.exe
