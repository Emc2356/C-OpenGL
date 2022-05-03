#pragma once
#include <vector>
#include <stdint.h>
#include <glad/glad.h>


class VertexBuffer {
public:
    VertexBuffer(float* data, uint32_t count, unsigned int usage=GL_STATIC_DRAW);
    VertexBuffer(std::vector<float> data, unsigned int usage=GL_STATIC_DRAW);
    ~VertexBuffer();
    void update_buffer(float* data, uint32_t size, uint32_t offset=0);
    void update_buffer(std::vector<float> data, uint32_t offset=0);
    void bind() const;
    void unbind() const;
    uint32_t get_count();
private:
    unsigned int m_RendererID;
    uint32_t m_count;
    uint32_t m_nbytes;
};
