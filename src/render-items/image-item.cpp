#include "image-item.hpp"
#include <GLES3/gl3.h>

const char *simple_vert = R"(
    #version 300 es
    precision mediump float;

    layout(location = 0) in vec2 pos;
    layout(location = 1) in vec2 uv;

    out vec2 frag_uv;

    void main() { 
        gl_Position = vec4(pos, 0.0, 1.0);
        frag_uv = uv;
    }
)";

const char *simple_frag = R"(
    #version 300 es
    precision mediump float;

    in vec2 frag_uv;
    out vec4 COLOR;

    void main() { 
        COLOR = vec4(frag_uv / 4.0, 0.0, 1.0); 
    }
)";

const float modelData[] = {
    1.0, -1.0, 1, 0.0, 
    1.0, 1.0, 1.0, 1.0,  
    -1.0, 1.0, 0.0, 1.0,
    -1.0, 1.0, 0.0, 1.0,
    -1.0, -1.0, 0.0, 0.0,
    1.0, -1.0, 1, 0.0, 
};

ImageItem::ImageItem() : shader(simple_vert, simple_frag) {
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->modelBuffer);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelData), modelData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
}

void ImageItem::render() {
    this->shader.use();

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
