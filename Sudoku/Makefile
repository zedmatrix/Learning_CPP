# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++23
PKG_CONFIG = pkg-config

# Files
SRC = main.cpp Sudoku.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = sudoku

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
