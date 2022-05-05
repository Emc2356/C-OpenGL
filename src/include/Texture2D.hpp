#pragma once

#include <string>
#include <glad/glad.h>


class Texture2D {
public:
    Texture2D(const std::string& filepath, bool flipped=false, int internalformat=GL_RGBA8, unsigned format=GL_RGBA, unsigned int type=GL_UNSIGNED_BYTE);
    Texture2D(const int width, const int height, unsigned char* buffer=nullptr, int internalformat=GL_RGBA8, unsigned format=GL_RGBA, unsigned int type=GL_UNSIGNED_BYTE);
    Texture2D();
    ~Texture2D();

    void update_data(unsigned char* buffer, int internalformat=GL_RGBA8, unsigned format=GL_RGBA, unsigned int type=GL_UNSIGNED_BYTE);
    void update_data(const std::string& filepath, bool flipped=false, int internalformat=GL_RGBA8, unsigned format=GL_RGBA, unsigned int type=GL_UNSIGNED_BYTE);

    void bind(unsigned int slot=0) const;
    void unbind() const;
  
    void set_filters(int min, int mag);
    void set_repeat_x(bool v);
    void set_repeat_y(bool v);

    inline int get_width() const;
    inline int get_height() const;
    inline int get_BPP() const;

private:
    unsigned int m_RendererID;
    std::string m_filepath;
    unsigned char* m_local_buffer;
    int m_width;
    int m_height;
    // bits per pixel
    int m_BPP;
    int m_internalformat;
    unsigned int m_format;
    unsigned int m_type;
};
