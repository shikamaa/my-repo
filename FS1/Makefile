CXX = g++
CXXFLAGS = -Wall -g

all: read-file

read-file: main.o
	$(CXX) $(CXXFLAGS) -o read-file main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	 rm -f read-file main.o
