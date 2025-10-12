.PHONY: all run clean

all: copy

copy: copy.o
    g++  copy.o -o copy

copy.o: copy.cpp
    g++ -c copy.cpp -o copy.o -Wall -Wextra -std=c++11

run: copy
    ./copy

clean:  
    rm -f *.o copy
~                          
