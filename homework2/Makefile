all: program

program: main.o
	g++ main.o -o program

main.o: main.cpp complex.h
	g++ -c main.cpp -o main.o

clean:
	rm -f *.o program

