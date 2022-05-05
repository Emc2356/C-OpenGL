#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glMessageCallback.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture2D.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "utils.hpp"


const int WIDTH = 960;
const int HEIGHT = 540;
const char* TITLE = "OpenGL thingy";


GLFWwindow* create_window(int width, int height, const char* title) {
    if (glfwInit() != GLFW_TRUE) {
        char buffer[1024];
        glfwGetError((const char**)&buffer);
        fprintf(stderr, "failed to initialzie GLFW due to: %s\n", buffer);
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        char buffer[1024];
        glfwGetError((const char**)&buffer);
        fprintf(stderr, "failed to create GLFW window due to: %s\n", buffer);
        exit(1);
    }

    glfwMakeContextCurrent(window);

    return window;
}


int main() {
    // glfwSetErrorCallback([](int error, const char* description) -> void { fprintf(stderr, "Glfw Error %d: %s\n", error, description); });
    glfwInit();
	GLFWwindow* window = create_window(WIDTH, HEIGHT, TITLE);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD.");
        exit(1);
	}

    Renderer renderer = Renderer(450, window);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   std::vector<float> vertices = {
        // x, y, z, u, v
        -50.0f, -50.0f, +0.0f, 0.0f, 1.0f - 0.0f,
        +50.0f, -50.0f, +0.0f, 1.0f, 1.0f - 0.0f,
        +50.0f, +50.0f, +0.0f, 1.0f, 1.0f - 1.0f,
        -50.0f, +50.0f, +0.0f, 0.0f, 1.0f - 1.0f 
    };
    
    std::vector<unsigned int> indices = {  
        0, 1, 2,  // first triangle
        0, 2, 3   // second triangle
    };

    glm::mat4 proj = glm::ortho<float>(0, WIDTH, 0, HEIGHT, -1, 1);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(50, 50, 0));

    Shader shader = Shader(read_file("shaders/shader.vert"), read_file("shaders/shader.frag"));
    Texture2D texture = Texture2D("resources/avatar-100.png", false);
    texture.set_filters(GL_LINEAR, GL_LINEAR);
    texture.set_repeat_x(false);
    texture.set_repeat_y(false);
    VertexBuffer vbo = VertexBuffer(vertices, GL_STATIC_DRAW);
    IndexBuffer ibo = IndexBuffer(indices, GL_STATIC_DRAW);
    VertexArray vao;
    VertexBufferLayout layout;
    layout.push<float>(3);  // x. y, z
    layout.push<float>(2);  // u, v
    vao.add_layout(vbo, layout);

    shader.unbind();
    vbo.unbind();
    ibo.unbind();
    vao.unbind();

    float time = 0;

	while (!glfwWindowShouldClose(window)) {
        renderer.start_frame();
        renderer.clear();

        shader.bind();
        ibo.bind();
        vao.bind();

        float xt;
        float yt;
        {
            ImGui::Begin("debug");
            ImGui::SliderFloat("x translate", &xt, 0.0f, WIDTH - 100);
            ImGui::SliderFloat("y translate", &yt, 0.0f, HEIGHT - 100);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(xt, yt, 0));

        glm::mat4 mvp = proj * view * model;

        shader.set_uniform("iTime", time);
        shader.set_uniform("iMVP", mvp);

        texture.bind(1);
        shader.set_uniform("iTexture", 1);

        ImGui::Render();

        renderer.draw(ibo, vao, shader, GL_TRIANGLES);

        renderer.end_frame();

		glfwSwapBuffers(window);
		glfwPollEvents();

        time += 0.005f;
	}

    glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
