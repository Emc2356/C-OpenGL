#pragma once
#include <glad/glad.h>
#include <vector>
#include <stdint.h>


class IndexBuffer {
public:
    IndexBuffer(unsigned int* data, uint32_t count, unsigned int usage=GL_STATIC_DRAW);
    IndexBuffer(std::vector<unsigned int> data, unsigned int usage=GL_STATIC_DRAW);
    ~IndexBuffer();
    void update_buffer(unsigned int* data, uint32_t size, uint32_t offset=0);
    void update_buffer(std::vector<unsigned int> data, uint32_t offset=0);
    void bind() const;
    void unbind() const;
    uint32_t get_count() const;
    unsigned int get_type() const;
private:
    unsigned int m_RendererID;
    unsigned int m_type;
    uint32_t m_count;
    uint32_t m_nbytes;
};
