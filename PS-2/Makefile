all: interactive_shell

interactive_shell: interactive_shell.o
	g++ interactive_shell.o -o interactive_shell

interactive_shell.o: interactive_shell.cpp
	g++ -c interactive_shell.cpp -o interactive_shell.o

clean:
	rm -f interactive_shell.o interactive_shell
