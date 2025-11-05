#pragma once
#include <GLES3/gl3.h>
#include <glm/glm.hpp>

class Shader {
    private:
        GLuint program;
        void check(GLuint shader);

    public:
        Shader(const char* vertSource, const char* fragSource);

        void use();

        void setUniform(const char* uniform, float value);
        void setUniform(const char* uniform, glm::vec2 value);
        void setUniform(const char* uniform, glm::vec3 value);
        void setUniform(const char* uniform, glm::vec4 value);
};
