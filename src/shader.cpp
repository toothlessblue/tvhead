#include "shader.hpp"
#include <GLES3/gl3.h>
#include <iostream>
#include <vector>

Shader::Shader(const char* vertSource, const char* fragSource) {
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
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        int maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    	std::vector<char> errorLog(maxLength);
	glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << &errorLog[0] << std::endl;
    };
}

void Shader::use() {
    glUseProgram(this->program);
}
