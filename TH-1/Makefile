all: array_summary

array_summary: array_summary.o
	g++ array_summary.o -o array_summary

array_summary.o: array_summary.cpp
	g++ -c array_summary.cpp -o array_summary.o

clean:
	rm -f array_summary.o array_summary
