#pragma once
#include "VertexBuffer.hpp"

struct VertexBufferLayoutElement {
    unsigned int type;
    unsigned int sizeof_type;
    unsigned int count;
    unsigned char normalized;
};

class VertexBufferLayout {
public:
    VertexBufferLayout() {
        m_stride = 0;
    }

    template<typename T>
    void push(const unsigned int count);

    inline const std::vector<VertexBufferLayoutElement>& get_elements() const { return m_elements; }
    inline unsigned int get_stride() const { return m_stride; }

private:
    std::vector<VertexBufferLayoutElement> m_elements;
    unsigned int m_stride;
};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void add_layout(VertexBuffer& vbo, VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;

private:
    unsigned int m_RendererID;
};
