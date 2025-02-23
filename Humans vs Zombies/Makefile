# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++23
PKG_CONFIG = pkg-config

# Files
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = Humans-vs-Zombies

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
