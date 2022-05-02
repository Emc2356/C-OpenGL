#include "VertexArray.hpp"
#include <assert.h>


template<typename T>
void VertexBufferLayout::push(const unsigned int count) {
    assert(false);
}
template<>
void VertexBufferLayout::push<float>(const unsigned int count) {
    VertexBufferLayoutElement el = { GL_FLOAT, 4, count, GL_FALSE };
    m_elements.push_back(el);
    m_stride += sizeof(float) * count;
}
template<>
void VertexBufferLayout::push<int>(const unsigned int count) {
    VertexBufferLayoutElement el = { GL_INT, 4, count, GL_FALSE };
    m_elements.push_back(el);
    m_stride += sizeof(int) * count;
}
template<>
void VertexBufferLayout::push<unsigned int>(const unsigned int count) {
    VertexBufferLayoutElement el = { GL_UNSIGNED_INT, 4, count, GL_FALSE };
    m_elements.push_back(el);
    m_stride += sizeof(unsigned int) * count;
}
template<>
void VertexBufferLayout::push<unsigned char>(const unsigned int count) {
    VertexBufferLayoutElement el = { GL_UNSIGNED_BYTE, 1, count, GL_TRUE };
    m_elements.push_back(el);
    m_stride += sizeof(unsigned char) * count;
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::add_layout(VertexBuffer& vbo, VertexBufferLayout& layout) {
    bind();
    vbo.bind();

    const auto& elements = layout.get_elements();

    unsigned int offset = 0;
    
    for (uint32_t i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (void*)offset);

        offset += element.count * element.sizeof_type;
    }
}
