#pragma once
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include <GLFW/glfw3.h>


class Renderer {
public:
    Renderer(const int& glsl_version, GLFWwindow* window);
    ~Renderer();
    void start_frame() const;
    void end_frame() const;
    void clear() const;
    void draw(const IndexBuffer& ibo, const VertexArray& vao, const Shader& shader, const unsigned int mode=GL_TRIANGLES) const;
};
