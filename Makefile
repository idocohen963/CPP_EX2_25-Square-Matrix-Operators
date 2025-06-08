CXX = g++
CXXFLAGS = -std=gnu++17 -Wall -Wextra -Iinclude

SRC = src/main.cpp src/SquareMat.cpp
TARGET = squaremat_demo

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)