#pragma once
#include <GLES3/gl3.h>

class Shader {
    private:
        GLuint program;

        void check(GLuint shader);

    public:
        Shader(const char* vertSource, const char* fragSource);

        void use();
};
