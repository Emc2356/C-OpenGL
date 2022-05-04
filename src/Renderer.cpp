#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui.h>

#include "Renderer.hpp"
#include <glad/glad.h>
#include <stdio.h>


Renderer::Renderer(const int& glsl_version, GLFWwindow* window) {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    // 8 for `#version` 1 for space and 3 for the version 
    char glsl_version_string[12];
    sprintf(glsl_version_string, "#version %d", glsl_version);
    ImGui_ImplOpenGL3_Init(glsl_version_string);
    ImGui::StyleColorsDark();
}

Renderer::~Renderer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::clear() const { 
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const IndexBuffer& ibo, const VertexArray& vao, const Shader& shader, const unsigned int mode/*=GL_TRIANGLES*/) const {
    shader.bind();
    ibo.bind();
    vao.bind();

    glDrawElements(mode, ibo.get_count(), ibo.get_type(), nullptr);
}

void Renderer::start_frame() const {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::end_frame() const {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
