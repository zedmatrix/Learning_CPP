# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23
PKG_CONFIG = pkg-config

# Dependency detection
SDL_CFLAGS  := $(shell $(PKG_CONFIG) --cflags sdl2)
SDL_LIBS    := $(shell $(PKG_CONFIG) --libs sdl2)
#GLEW_CFLAGS   := $(shell $(PKG_CONFIG) --cflags glew)
GLEW_LIBS   := $(shell $(PKG_CONFIG) --libs glew)
#TTF_CFLAGS  := $(shell $(PKG_CONFIG) --cflags SDL2_ttf)
#TTF_LIBS    := $(shell $(PKG_CONFIG) --libs SDL2_ttf)

#Ensure both SDL2 and GLEW are available
ifeq ($(strip $(SDL_LIBS)),)
    $(error "SDL2 libs not found.")
endif
ifeq ($(strip $(GLEW_LIBS)),)
    $(error "GLEW libs not found.")
endif

# Final flags
CXXFLAGS += $(SDL_CFLAGS) #$(TTF_CFLAGS) #$(GLEW_CFLAGS)
LDLIBS += $(SDL_LIBS) $(GLEW_LIBS) #$(TTF_LIBS)

# Source/Object files directory
SRC_DIR := src
OBJ_DIR := obj

# Source files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
TARGET = opengl-io

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ_DIR):
	mkdir -pv $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

print-vars:
	@echo "SDL_CFLAGS: $(SDL_CFLAGS)"
	@echo "SDL_LIBS: $(SDL_LIBS)"
	@echo "GLEW_FLAGS: $(GLEW_LIBS)"
	@echo "GLEW_LIBS: $(GLEW_LIBS)"
	@echo "TTF_CFLAGS: ${TTF_CFLAGS}"
	@echo "TTF_LIBS: ${TTF_LIBS}"

.PHONY: all clean print-vars $(OBJ_DIR)
