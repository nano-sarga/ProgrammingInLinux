# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -O2

# Название исполняемого файла
TARGET = simple-copy
SRC = simple-copy.cpp

# Цель по умолчанию
all: $(TARGET)

# Сборка программы
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Очистка
clean:
	rm -f $(TARGET)

