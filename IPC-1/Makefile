CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
TARGET = Handler

all: $(TARGET)

$(TARGET): Handler.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) Handler.o

Handler.o: Handler.cpp
	$(CXX) $(CXXFLAGS) -c Handler.cpp

clean:
	rm -f Handler.o Handler
