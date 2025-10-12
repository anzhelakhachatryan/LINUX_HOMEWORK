.PHONY: all run clean

all: do-command

do-command: do-command.o
	g++ do-command.o -o do-command

do-command.o: do-command.cpp
	g++ -c do-command.cpp -o do-command.o -Wall -Wextra -std=c++11

clean: 
	rm -f *.o do-command
