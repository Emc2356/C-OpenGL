#pragma once

#include <string>


class Texture {
public:
    Texture(const std::string& filepath, bool flipped=false);
    ~Texture();

    inline int get_width() const { return m_width; }
    inline int get_height() const { return m_height; }

    void bind(unsigned int slot=0) const;
    void unbind() const;

private:
    unsigned int m_RendererID;
    std::string m_filepath;
    unsigned char* m_local_buffer;
    int m_width;
    int m_height;
    // bits per pixel
    int m_BPP;
};
