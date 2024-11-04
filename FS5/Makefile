CXX = g++
CXXFLAGS = -Wall -Wextra -O2

TARGET = manual-append
SOURCES = manual-append.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
