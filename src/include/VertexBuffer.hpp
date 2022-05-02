#pragma once
#include <vector>
#include <stdint.h>
#include <glad/glad.h>


class VertexBuffer {
public:
    VertexBuffer(float* data, uint32_t count, unsigned int usage);
    VertexBuffer(float* data, uint32_t count);
    VertexBuffer(std::vector<float> data, unsigned int usage);
    VertexBuffer(std::vector<float> data);
    ~VertexBuffer();
    void update_buffer(float* data, uint32_t size, uint32_t offset) ;
    void update_buffer(float* data, uint32_t size);
    void update_buffer(std::vector<float> data, uint32_t offset);
    void update_buffer(std::vector<float> data);
    void bind() const;
    void unbind() const;
    uint32_t get_count();
private:
    unsigned int m_RendererID;
    uint32_t m_count;
    uint32_t m_nbytes;
};
