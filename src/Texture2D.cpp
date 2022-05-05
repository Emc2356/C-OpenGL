#include "Texture2D.hpp"
#include <stb_image.h>
#include <stdexcept>
#include <string.h>


Texture2D::Texture2D() { 
    m_RendererID = 0;
    m_filepath = "";
    m_local_buffer = nullptr;
    m_width = 0;
    m_height = 0;
    m_BPP = 0;
    m_internalformat = 0;
    m_format = 0;
    m_type = 0;
}

Texture2D::Texture2D(const std::string& filepath, bool flipped/*=false*/, int internalformat/*=GL_RGBA8*/, unsigned format/*=GL_RGBA*/, unsigned int type/*=GL_UNSIGNED_BYTE*/) {
    stbi_set_flip_vertically_on_load(flipped ? 1 : 0);

    if (!(m_local_buffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BPP, 4))) {
        std::string failure_reason = (std::string)stbi_failure_reason();
        throw std::runtime_error("failed to load image `" + filepath + "` for the Texture2D: " + failure_reason + "\n");
    }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, m_width, m_height, 0, format, type, m_local_buffer);

    stbi_image_free(m_local_buffer);
}

Texture2D::Texture2D(const int width, const int height, unsigned char* buffer/*=nullptr*/, int internalformat/*=GL_RGBA8*/, unsigned format/*=GL_RGBA*/, unsigned int type/*=GL_UNSIGNED_BYTE*/) {
    m_internalformat = internalformat;
    m_width = width;
    m_height = height;
    m_format = format;
    m_type = type;
    m_local_buffer = buffer;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalformat, m_width, m_height, 0, m_format, m_type, m_local_buffer);
}

void Texture2D::update_data(unsigned char* buffer, int internalformat/*=GL_RGBA8*/, unsigned format/*=GL_RGBA*/, unsigned int type/*=GL_UNSIGNED_BYTE*/) {
    m_internalformat = internalformat;
    m_format = format;
    m_type = type;
    m_local_buffer = buffer;

    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalformat, m_width, m_height, 0, m_format, m_type, m_local_buffer);
}

void Texture2D::update_data(const std::string& filepath, bool flipped/*=false*/, int internalformat/*=GL_RGBA8*/, unsigned format/*=GL_RGBA*/, unsigned int type/*=GL_UNSIGNED_BYTE*/) {
    m_internalformat = internalformat;
    m_format = format;
    m_type = type;
    m_filepath = filepath;

    bind();

    stbi_set_flip_vertically_on_load(flipped ? 1 : 0);

    if (!(m_local_buffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BPP, 4))) {
        std::string failure_reason = (std::string)stbi_failure_reason();
        throw std::runtime_error("failed to load image `" + filepath + "` for the Texture2D: " + failure_reason + "\n");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalformat, m_width, m_height, 0, m_format, m_type, m_local_buffer);
    
    stbi_image_free(m_local_buffer);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_RendererID);
}

void Texture2D::set_filters(int mag, int min) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture2D::set_repeat_x(bool v) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, v ? GL_REPEAT : GL_CLAMP_TO_EDGE);
}

void Texture2D::set_repeat_y(bool v) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, v ? GL_REPEAT : GL_CLAMP_TO_EDGE);
}


void Texture2D::bind(unsigned int slot /*=0*/) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture2D::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture2D::get_width() const { return m_width; }
int Texture2D::get_height() const { return m_height; }
int Texture2D::get_BPP() const { return m_BPP; }
