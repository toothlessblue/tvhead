#include "gl2.h"

class Shader {
    private:
        GLuint program;

        void check(GLuint shader);

    public:
        Shader(char* vertSource, char* fragSource);

        void use();
};
