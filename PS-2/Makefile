CXX = g++
CXXFLAGS = -std=c++17

SRC = interactive-shell.cpp
TARGET = interactive-shell

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o *.log
