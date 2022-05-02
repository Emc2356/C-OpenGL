#include "VertexBuffer.hpp"


VertexBuffer::VertexBuffer(float* data, uint32_t count, unsigned int usage) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), (void*)data, usage);

    m_count = count;
    m_nbytes = count * sizeof(float);
}

VertexBuffer::VertexBuffer(float* data, uint32_t count) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), (void*)data, GL_STATIC_DRAW);

    m_count = count;
    m_nbytes = count * sizeof(float);
}

VertexBuffer::VertexBuffer(std::vector<float> data, unsigned int usage) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), (void*)data.data(), usage);

    m_count = data.size();
    m_nbytes = data.size() * sizeof(float);
}

VertexBuffer::VertexBuffer(std::vector<float> data) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), (void*)data.data(), GL_STATIC_DRAW);

    m_count = data.size();
    m_nbytes = data.size() * sizeof(float);
}

uint32_t VertexBuffer::get_count() {
    return m_count;
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::update_buffer(float* data, uint32_t size, uint32_t offset) { 
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size * sizeof(float), data);    
}

void VertexBuffer::update_buffer(float* data, uint32_t size) { 
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), data);    
}

void VertexBuffer::update_buffer(std::vector<float> data, uint32_t offset) { 
    bind(); 
    glBufferSubData(GL_ARRAY_BUFFER, offset, data.size() * sizeof(float), data.data());
}

void VertexBuffer::update_buffer(std::vector<float> data) { 
    bind(); 
    glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(float), (void*)data.data());
}

