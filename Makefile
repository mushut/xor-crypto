all: xor-test.exe

xor-test.exe: main.o
	g++ -o xor-test.exe main.o

xor-test.o: main.cpp
	g++ -c main.cpp

clean:
	rm main.o xor-test.exe
