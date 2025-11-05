#pragma once
#include "../render-item.hpp"
#include "../shader.hpp"
#include <GLES3/gl3.h>

class ImageItem : public RenderItem {
    Shader shader;
    GLuint vao;
    GLuint modelBuffer;

    public:
        ImageItem();

        void render(float time) override;
};
