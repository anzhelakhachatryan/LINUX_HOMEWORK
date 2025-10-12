.PHONY: all run clean

all: hacker-rm

hacker-rm: hacker-rm.o
	g++  hacker-rm.o -o hacker-rm

hacker-rm.o: hacker-rm.cpp
	g++ -c hacker-rm.cpp -o hacker-rm.o -Wall -Wextra -std=c++11

clean:  
	rm -f *.o hacker-rm


