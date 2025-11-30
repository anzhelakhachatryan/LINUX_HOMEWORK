CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=gnu++17
SRC = prime_calc.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = prime_calc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
