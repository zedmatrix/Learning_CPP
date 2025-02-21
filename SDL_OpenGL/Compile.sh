build="main.cpp MainGame.cpp Sprite.cpp"
echo "Compiling $build ..."
file="SDL_Test"

g++ -std=c++23 $(pkg-config --cflags --libs sdl2 gl) -lGLEW $build -o $file

if [ $? -eq 0 ]; then
    echo "Compilation successful! Output: $file"
else
    echo "Compilation failed!"
fi

