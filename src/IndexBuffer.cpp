#include "IndexBuffer.hpp"


IndexBuffer::IndexBuffer(unsigned int* data, uint32_t count, unsigned int usage/*=GL_STATIC_DRAW*/) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), (void*)data, usage);

    m_count = count;
    m_nbytes = count * sizeof(unsigned int);
    m_type = GL_UNSIGNED_INT;
}

IndexBuffer::IndexBuffer(std::vector<unsigned int> data, unsigned int usage/*=GL_STATIC_DRAW*/) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), (void*)data.data(), usage);

    m_count = data.size();
    m_nbytes = data.size() * sizeof(unsigned int);
    m_type = GL_UNSIGNED_INT;
}

uint32_t IndexBuffer::get_count() const {
    return m_count;
}

unsigned int IndexBuffer::get_type() const { 
    return m_type;
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::update_buffer(unsigned int* data, uint32_t size, uint32_t offset/*=0*/) {
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size * sizeof(unsigned int), data);    
}

void IndexBuffer::update_buffer(std::vector<unsigned int> data, uint32_t offset/*=0*/) {
    bind(); 
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, data.size() * sizeof(unsigned int), data.data());
}
