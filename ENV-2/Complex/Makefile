all: main

main: main.o Complex.o Sorted.o
	g++ main.o Complex.o Sorted.o -o main

main.o: src/main.cpp include/Complex.h include/Sorted.h
	g++ -c src/main.cpp -I./include -o main.o

Complex.o: src/Complex.cpp include/Complex.h
	g++ -c src/Complex.cpp -I./include -o Complex.o

Sorted.o: src/Sorted.cpp include/Sorted.h include/Complex.h
	g++ -c src/Sorted.cpp -I./include -o Sorted.o

run: main
	./main

clean:
	rm -f *.o main         
