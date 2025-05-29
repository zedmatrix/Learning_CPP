#!/bin/bash
File=Browser
Source="browser.cpp main.cpp"

echo "Compiling $Source ..."
libs="$(pkg-config --cflags --libs gtk4 webkitgtk-6.0)"

# Compile
g++ -fPIC -std=c++23 -lstdc++ $Source $libs -o $File

# Check for success
if [[ $? -eq 0 ]]; then
    echo "Compilation successful! Output: $File"
else
    echo "Compilation failed!"
fi
