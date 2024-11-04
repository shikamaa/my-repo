CXX = g++
CXXFLAGS = -Wall -Wextra -O2

TARGET = redirect-cin
SOURCES = redirect-cin.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
