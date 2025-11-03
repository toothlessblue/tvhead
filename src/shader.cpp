#include "shader.hpp"
#include "gl2.h"
#include <iostream>

Shader::Shader(char* vertSource, char* fragSource) {
    this->program = glCreateProgram();
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    auto frag = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vert, 1, &vertSource, NULL);
    glShaderSource(frag, 1, &fragSource, NULL);

    glCompileShader(vert);
    glCompileShader(frag);

    this->check(vert);
    this->check(frag);
    
    glAttachShader(this->program, vert);
    glAttachShader(this->program, frag);

    glLinkProgram(this->program);
}

void Shader::check(GLuint shader) {
    char infoLog[512];
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    };
}

void Shader::use() {
    glUseProgram(this->program);
}
