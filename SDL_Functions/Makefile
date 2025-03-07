# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -std=c++23
PKG_CONFIG = pkg-config

# Dependency detection
SDL_CFLAGS  := $(shell $(PKG_CONFIG) --cflags sdl2)
SDL_LIBS    := $(shell $(PKG_CONFIG) --libs sdl2)
# GLEW_CFLAGS   := $(shell $(PKG_CONFIG) --cflags glew)
# GLEW_LIBS   := $(shell $(PKG_CONFIG) --libs glew)
# TTF_CFLAGS  := $(shell $(PKG_CONFIG) --cflags SDL2_ttf)
# TTF_LIBS    := $(shell $(PKG_CONFIG) --libs SDL2_ttf)

#Ensure both SDL2 and GLEW are available
ifeq ($(strip $(SDL_LIBS)),)
    $(error "SDL2 libs not found.")
endif
# ifeq ($(strip $(GLEW_LIBS)),)
#     $(error "GLEW libs not found.")
# endif

# Final flags
CFLAGS += $(SDL_CFLAGS) #$(GLEW_CFLAGS) $(TTF_CFLAGS)
LDLIBS += $(SDL_LIBS) #$(GLEW_LIBS) $(TTF_LIBS)

# Files
SRC = main.cpp MainWindow.cpp GameSystem.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = window_test

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

print-vars:
	@echo "SDL_CFLAGS: $(SDL_CFLAGS)"
	@echo "SDL_LIBS: $(SDL_LIBS)"
	@echo "GLEW_FLAGS: $(GLEW_LIBS)"
	@echo "GLEW_LIBS: $(GLEW_LIBS)"
	@echo "TTF_CFLAGS: ${TTF_CFLAGS}"
	@echo "TTF_LIBS: ${TTF_LIBS}"
