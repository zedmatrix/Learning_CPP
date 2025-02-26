# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++23

# Files
SRC = main.cpp TicTacToeGame.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = TicTacToeGame

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
