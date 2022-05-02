#include "Shader.hpp"
#include <stdio.h>
#include <stdexcept>
#include <vector>


static unsigned int compile_shader(unsigned int type, const std::string& source) {
    char* type_str;
    switch (type) {
    case GL_VERTEX_SHADER:
        type_str = (char*)"vertex";
        break;
    case GL_FRAGMENT_SHADER:
        type_str = (char*)"fragment";
        break;
    case GL_GEOMETRY_SHADER:
        type_str = (char*)"geometry";
        break;
    case GL_COMPUTE_SHADER:
        type_str = (char*)"compute";
        break;
    default:
        fprintf(stderr, "unrecognized shader type: %d\n", type);
        return 0;
    }
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> message(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message.data());

        fprintf(stderr, "failed while compiling %s shader!\n%s", type_str, message.data());

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int compile_program(const std::string& vertex_source, const std::string& fragment_source) {
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_source.c_str());
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

    if (!vs || !fs) {
        throw std::runtime_error("failed while creating the shader");
    }

    int id = glCreateProgram();

    glAttachShader(id, vs);
    glAttachShader(id, fs);

    glLinkProgram(id);

    int linked;
    glGetProgramiv(id, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> message(length * sizeof(char));
        glGetProgramInfoLog(id, length, &length, message.data());

        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(id);

        throw std::runtime_error((std::string)"failed while linking the program\n==========\n" + (std::string)message.data());
    }

    glValidateProgram(id);

    int valid;
    glGetProgramiv(id, GL_LINK_STATUS, &valid);
    if (valid == GL_FALSE) {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> message(length * sizeof(char));
        glGetProgramInfoLog(id, length, &length, message.data());

        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(id);
        
        throw std::runtime_error((std::string)"program can not run\n==========\n" + (std::string)message.data());
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return id;
}

Shader::Shader(const std::string& vertex_source, const std::string& fragment_source) {
    m_RendererID = compile_program(vertex_source, fragment_source);

    int uniform_count;
    glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &uniform_count);
    std::vector<char> uniform_name(1024);
    int size;
    unsigned int type;
    for (int loc = 0; loc < uniform_count; loc++) {
        glGetActiveUniform(m_RendererID, loc, uniform_name.size(), nullptr, &size, &type, uniform_name.data());

        m_uniforms[(std::string)uniform_name.data()] = UniformData(
            (std::string)uniform_name.data(), 
            loc,
            type,
            m_RendererID
        );
    }
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::bind() const {
    glUseProgram(m_RendererID);
}

void Shader::unbind() const {
    glUseProgram(0);
}
