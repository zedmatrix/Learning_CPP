#include <cstddef>
#include <random>
#include "Sprite.hpp"
#include "Vertex.hpp"
#include "ResourceManager.hpp"
#include "zengine.hpp"

namespace zengine {

    Sprite::Sprite() {
        _vboID = 0;
    }

    Sprite::~Sprite() {
        if (_vboID != 0) {
            glDeleteBuffers(1, &_vboID);
        }
    }
    void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
        _texture = ResourceManager::getTexture(texturePath);

        if (_vboID == 0) {
            glGenBuffers(1, &_vboID);
        }
        // std::random_device::result_type seed = std::random_device()();
        // std::mt19937 randomEngine(seed);
        Vertex vertexData[6];

        //First Triangle
        vertexData[0].setPos(x + width, y + height);
        vertexData[0].setUV(1.0f, 1.0f);

        vertexData[1].setPos(x, y + height);
        vertexData[1].setUV(0.0f, 1.0f);

        vertexData[2].setPos(x, y);
        vertexData[2].setUV(0.0f, 0.0f);

        // Second Triangle
        vertexData[3].setPos(x, y);
        vertexData[3].setUV(0.0f, 0.0f);

        vertexData[4].setPos(x + width, y);
        vertexData[4].setUV(1.0f, 0.0f);

        vertexData[5].setPos(x + width, y + height);
        vertexData[5].setUV(1.0f, 1.0f);

        for (int i = 0; i < 6; i++) {
            vertexData[i].setColor(200, 100, 150, 128);
        }
        vertexData[1].setColor(100, 150, 100, 255);
        vertexData[4].setColor(150, 200, 100, 128);


        // Bind gl Buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);

        // Upload data to buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // Unbind gl Buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Sprite::draw() {
        // bind texture
        glBindTexture(GL_TEXTURE_2D, _texture.id);

        //bind the buffer object
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);

        glEnableVertexAttribArray(0);

        // Position Attribute pointer // (void*)
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

        glDrawArrays( GL_TRIANGLES, 0, 6);

        //disable the vertex attribute
        glDisableVertexAttribArray(0);

        // Unbind the buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
