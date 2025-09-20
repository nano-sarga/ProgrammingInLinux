TARGET = Complex
CC = g++

all: $(TARGET)

main.o: main.cpp Complex.h SortComplex.h
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o

Complex.o: Complex.cpp Complex.h
	$(CC) $(CXXFLAGS) -c Complex.cpp -o Complex.o

SortComplex.o: SortComplex.cpp SortComplex.h Complex.h
	$(CC) $(CXXFLAGS) -c SortComplex.cpp -o SortComplex.o

$(TARGET): main.o Complex.o SortComplex.o
	$(CC) main.o Complex.o SortComplex.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
