#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glMessageCallback.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
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
    glfwInit();
	GLFWwindow* window = create_window(WIDTH, HEIGHT, TITLE);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD.");
        exit(1);
	}

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   std::vector<float> vertices = {
        // x, y, z, u, v
        +000.0f, +000.0f, +0.0f, 0.0f, 1.0f - 0.0f,
        +500.0f, +000.0f, +0.0f, 1.0f, 1.0f - 0.0f,
        +500.0f, +500.0f, +0.0f, 1.0f, 1.0f - 1.0f,
        +000.0f, +500.0f, +0.0f, 0.0f, 1.0f - 1.0f 
    };
    
    std::vector<unsigned int> indices = {  
        0, 1, 2,  // first triangle
        0, 2, 3   // second triangle
    };

    glm::mat4 proj = glm::ortho<float>(0, WIDTH, 0, HEIGHT, -1, 1);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;

    Shader shader = Shader(read_file("shaders/shader.vert"), read_file("shaders/shader.frag"));
    Texture texture = Texture("resources/avatar.png", false);
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
        shader.bind();
        ibo.bind();
        vao.bind();

        shader.set_uniform("iTime", time);
        shader.set_uniform("iMVP", mvp);

        texture.bind(1);
        shader.set_uniform("iTexture", 1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();

        time += 0.005f;
	}

	glfwTerminate();
	return 0;
}
