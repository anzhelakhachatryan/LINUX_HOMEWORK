.PHONY: all run clean

all: manual-append

manual-append: manual-append.o
	g++  manual-append.o -o manual-append

manual-append.o: manual-append.cpp
	g++ -c manual-append.cpp -o manual-append.o -Wall -Wextra -std=c++11

run: manual-append
	./manual-append

clean:  
	rm -f *.o manual-append
