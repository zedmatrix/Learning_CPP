# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++23
PKG_CONFIG = pkg-config

# Files
SRC = main.cpp Elements.cpp Molecules.cpp Organism.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = Molecules

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
