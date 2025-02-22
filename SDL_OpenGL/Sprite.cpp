#include "Sprite.h"
#include <cmath>
#include <numbers>

//Constructor
Sprite::Sprite() {
    _vboID = 0;
    _iboID = 0;

}

//Desctructor
Sprite::~Sprite() {

    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
    if (_iboID != 0) {
        glDeleteBuffers(1, &_iboID);
    }
}

void Sprite::init(float x, float y, float width, float height, int sides) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _sides = sides;

    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }
    if (_iboID == 0) {
        glGenBuffers(1, &_iboID);
    }

    const float radius = 50.0f;
    const float angleStep = 2.0f * M_PI / _sides;

    float vertexData[(_sides + 1) * 2];
    // Center point
    vertexData[0] = _x + _width;
    vertexData[1] = _y + _height;

    // Pentagon outer points
    for (int i = 0; i < _sides; i++) {
        float angle = i * angleStep;
        vertexData[2 + i * 2] = vertexData[0] + radius * cos(angle);
        vertexData[3 + i * 2] = vertexData[1] + radius * sin(angle);
    }

    unsigned int indices[_sides * 3];
    for (int i = 0; i < _sides; i++) {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = (i + 1) % _sides + 1;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //delete[] vertexData;
    //delete[] indices;

}

void Sprite::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
    glDrawElements(GL_TRIANGLES, _sides * 3, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 18);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
