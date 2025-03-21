#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <algorithm>
#include "Manager.hpp"
#include "Vertex.hpp"

enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

struct RenderBatch {
    GLuint offset;
    GLuint numVertices;
    GLuint texture;

    RenderBatch(GLuint off, GLuint numVerts, GLuint tex)
        : offset(off), numVertices(numVerts), texture(tex) {}
};

struct Glyph {
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;

};

class Sprite {

public:
    Sprite() : _vbo(0), _vao(0) {}

    void init();
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
    void renderBatch();

private:

    void createRenderBatches();
    void createVertexArray();
    void sortGlyphs();
    GLuint _vbo;
    GLuint _vao;
    std::vector<Glyph> _glyphs;
    std::vector<RenderBatch> _renderBatches;
    GlyphSortType _sortType;

};

#endif //SPRITE_HPP
