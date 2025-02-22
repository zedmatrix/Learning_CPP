#pragma once
#include <GL/glew.h>

class Sprite
{

public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height, int sides);
    void draw();
private:
    float _x;
    float _y;
    float _width;
    float _height;
    int _sides = 6;
    GLuint _vboID;
    GLuint _iboID;

};
