CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

TARGET = read-file

SRCS = read-file.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

