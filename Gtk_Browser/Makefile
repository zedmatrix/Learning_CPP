# Makefile
CXX = g++
CXXFLAGS = -fPIC -std=c++23 $(shell pkg-config --cflags gtk4 webkitgtk-6.0)
LDFLAGS = $(shell pkg-config --libs gtk4 webkitgtk-6.0)
SRC = browser.cpp main.cpp
OUT = Browser

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OUT)
