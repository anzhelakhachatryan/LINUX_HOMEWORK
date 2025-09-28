.PHONY: all run clean

all: read_posix

read_posix: read_posix.o
	g++  read_posix.o -o read_posix

read_posix.o: read_posix.cpp
	g++ -c read_posix.cpp -o read_posix.o -Wall -Wextra -std=c++11

run: read_posix
	./read_posix 

clean:  
	rm -f *.o read_posix
