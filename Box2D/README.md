# My Box2D - SDL2 - OpenGL Experiments

<br>For C++23 and using meson.build

# Installation

1. Create a new directory and initialize git
```
git clone --filter=blob:none --no-checkout https://github.com/zedmatrix/Learning_CPP.git
cd Learning_CPP
```

2. Enable sparse checkout: `git sparse-checkout init --cone`

3. Set the directory you want: `git sparse-checkout set Box2D`

4. Checkout the files: `git checkout`

## Building
```
cd Box2d
mkdir -v build
meson setup ..
ninja
cp -rv ../assets .
./box2d_demo
```

# Acknowledgments

[Benjamin Arnold](https://github.com/Barnold1953/GraphicsTutorials/tree/master)
[Advanced C++/Graphics Tutorials](https://www.youtube.com/playlist?list=PLSPw4ASQYyymu3PfG9gxywSPghnSMiOAW)
