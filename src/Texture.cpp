#include "Texture.hpp"
#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture(const std::string& filepath) {
    m_RendererID = 0;
    m_filepath = filepath;
    m_local_buffer = nullptr;
    m_width = 0;
    m_height = 0;
    m_BPP = 0;

    stbi_set_flip_vertically_on_load(1);
    m_local_buffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);

    unbind();

    if (m_local_buffer != nullptr) {
        stbi_image_free(m_local_buffer);
    } 
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);
}

void Texture::bind(unsigned int slot /*=0*/) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
