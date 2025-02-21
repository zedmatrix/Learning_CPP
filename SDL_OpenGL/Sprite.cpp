#include "Sprite.h"
#include <cmath>
#include <numbers>

//Constructor
Sprite::Sprite() {
    _vboID = 0;

}

//Desctructor
Sprite::~Sprite() {
    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::init(float x, float y, float width, float height) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }
    float vertexData[12];
    const float radius = 50.0f;
    const int sides = 6;
    const float angleStep = 2.0f * M_PI / sides;

    // Center point
    vertexData[0] = _x + _width;
    vertexData[1] = _y + _height;

    // Pentagon outer points
    for (int i = 0; i < sides; i++) {
        float angle = i * angleStep;
        vertexData[2 + i * 2] = vertexData[0] + radius * cos(angle);
        vertexData[3 + i * 2] = vertexData[1] + radius * sin(angle);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
