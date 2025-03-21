#include "Sprite.hpp"

void Sprite::init() {
    createVertexArray();

}

void Sprite::begin(GlyphSortType sortType /*GlyphSortType::TEXTURE */) {
    _sortType = sortType;
    _renderBatches.clear();
    _glyphs.clear();
}

void Sprite::end() {
    sortGlyphs();
    createRenderBatches();
}

void Sprite::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {

    Glyph newGlyph;
    newGlyph.texture = texture;
    newGlyph.depth = depth;

    // Set up vertices using setter functions
    newGlyph.topLeft.setPos(destRect.x, destRect.y + destRect.w);
    newGlyph.topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
    newGlyph.topLeft.color = color;

    newGlyph.bottomLeft.setPos(destRect.x, destRect.y);
    newGlyph.bottomLeft.setUV(uvRect.x, uvRect.y);
    newGlyph.bottomLeft.color = color;

    newGlyph.topRight.setPos(destRect.x + destRect.z, destRect.y + destRect.w);
    newGlyph.topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    newGlyph.topRight.color = color;

    newGlyph.bottomRight.setPos(destRect.x + destRect.z, destRect.y);
    newGlyph.bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
    newGlyph.bottomRight.color = color;

    // Add to the list
    _glyphs.emplace_back(std::move(newGlyph));

}

void Sprite::createRenderBatches() {
    std::vector <Vertex> vertices;
    vertices.resize(_glyphs.size() * 6);

    if (_glyphs.empty()) return;

    int offset{0};
    int currentVertex{0};
    _renderBatches.emplace_back(offset, 6, _glyphs[0].texture);
    vertices[currentVertex++] = _glyphs[0].topLeft;
    vertices[currentVertex++] = _glyphs[0].bottomLeft;
    vertices[currentVertex++] = _glyphs[0].bottomRight;
    vertices[currentVertex++] = _glyphs[0].bottomRight;
    vertices[currentVertex++] = _glyphs[0].topRight;
    vertices[currentVertex++] = _glyphs[0].topLeft;
    offset += 6;

    for (int currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++) {

        if (_glyphs[currentGlyph].texture != _glyphs[currentGlyph - 1].texture) {
            _renderBatches.emplace_back(offset, 6, _glyphs[0].texture);
        } else {
            _renderBatches.back().numVertices += 6;
        }
        vertices[currentVertex++] = _glyphs[currentGlyph].topLeft;
        vertices[currentVertex++] = _glyphs[currentGlyph].bottomLeft;
        vertices[currentVertex++] = _glyphs[currentGlyph].bottomRight;
        vertices[currentVertex++] = _glyphs[currentGlyph].bottomRight;
        vertices[currentVertex++] = _glyphs[currentGlyph].topRight;
        vertices[currentVertex++] = _glyphs[currentGlyph].topLeft;
        offset += 6;

    }
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void Sprite::createVertexArray() {
    if (_vao == 0) glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    if (_vbo == 0) glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Position Attribute pointer // (void*)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void Sprite::sortGlyphs() {
    switch (_sortType) {
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort(_glyphs.begin(), _glyphs.end(),
                [](const Glyph& a, const Glyph& b) { return a.depth < b.depth; });
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(_glyphs.begin(), _glyphs.end(),
                [](const Glyph& a, const Glyph& b) { return a.depth > b.depth; });
            break;
        case GlyphSortType::TEXTURE:
            std::stable_sort(_glyphs.begin(), _glyphs.end(),
                [](const Glyph& a, const Glyph& b) { return a.texture < b.texture; });
            break;
        case GlyphSortType::NONE:
            break;
    }
}
void Sprite::renderBatch() {
    glBindVertexArray(_vao);
    GLuint lastTexture = 0;
    for (const auto& batch : _renderBatches) {
        if (batch.texture != lastTexture) {
            glBindTexture(GL_TEXTURE_2D, batch.texture);
            lastTexture = batch.texture;
        }
        glDrawArrays(GL_TRIANGLES, batch.offset, batch.numVertices);
    }
    glBindVertexArray(0);
}
