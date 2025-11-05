#include "shader.hpp"
#include <GLES3/gl3.h>
#include <iostream>
#include <vector>

Shader::Shader(const char *vertSource, const char *fragSource) {
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

void Shader::use() { glUseProgram(this->program); }

void Shader::setUniform(const char *uniform, glm::vec2 value) {
    this->use();

    unsigned int location = glGetUniformLocation(this->program, uniform);
    glUniform2fv(location, 2, &value[0]);
}

void Shader::setUniform(const char *uniform, float value) {
    this->use();

    unsigned int location = glGetUniformLocation(this->program, uniform);
    glUniform1f(location, value);
}

void Shader::setUniform(const char *uniform, glm::vec3 value) {
    this->use();

    unsigned int location = glGetUniformLocation(this->program, uniform);
    glUniform3fv(location, 3, &value[0]);
}

void Shader::setUniform(const char *uniform, glm::vec4 value) {
    this->use();

    unsigned int location = glGetUniformLocation(this->program, uniform);
    glUniform4fv(location, 4, &value[0]);
}
