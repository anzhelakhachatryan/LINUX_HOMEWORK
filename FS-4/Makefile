.PHONY: all run clean

all: redirect-cin

redirect-cin: redirect-cin.o
	g++  redirect-cin.o -o redirect-cin

redirect-cin.o: redirect-cin.cpp
	g++ -c redirect-cin.cpp -o redirect-cin.o -Wall -Wextra -std=c++11

clean: 
	rm -f *.o redirect-cin   
