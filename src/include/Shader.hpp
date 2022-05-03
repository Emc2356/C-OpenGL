#pragma once
#include <string>
#include <unordered_map>
#include <glad/glad.h>

// just to make the lint shut up
#ifdef NOT_DEFINED
#include <optional>
#else
#include <experimental/optional>

namespace std {
    using std::experimental::optional;
}
#endif

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


struct UniformData {
public:
    UniformData(const std::string& name_, const int location_, const unsigned int type_, unsigned int shaderID) : 
    name(name_), location(location_), type(type_), m_shaderID(shaderID) {}
    UniformData() : 
    name(""), location(0), type(0), m_shaderID(0) {}

    std::string name;
    int location;
    unsigned int type;

    unsigned int get_shader_id() const { return m_shaderID; }

    inline void set_uniform(const int&        v) const { glUniform1i(location, v); }
    inline void set_uniform(const glm::ivec2& v) const { glUniform2i(location, v.x, v.y); }
    inline void set_uniform(const glm::ivec3& v) const { glUniform3i(location, v.x, v.y, v.z); }
    inline void set_uniform(const glm::ivec4& v) const { glUniform4i(location, v.x, v.y, v.z, v.w); }
    inline void set_uniform(const bool&       v) const { glUniform1i(location, v); }
    inline void set_uniform(const glm::bvec2& v) const { glUniform2i(location, v.x, v.y); }
    inline void set_uniform(const glm::bvec3& v) const { glUniform3i(location, v.x, v.y, v.z); }
    inline void set_uniform(const glm::bvec4& v) const { glUniform4i(location, v.x, v.y, v.z, v.w); }
    inline void set_uniform(const float&      v) const { glUniform1f(location, v); }
    inline void set_uniform(const glm::vec2&  v) const { glUniform2f(location, v.x, v.y); }
    inline void set_uniform(const glm::vec3&  v) const { glUniform3f(location, v.x, v.y, v.z); }
    inline void set_uniform(const glm::vec4&  v) const { glUniform4f(location, v.x, v.y, v.z, v.w); }
    inline void set_uniform(const glm::mat4&  v) const { glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(v)); }
    inline void set_uniform(const double&     v) const { glUniform1d(location, v); }
    inline void set_uniform(const glm::dvec2& v) const { glUniform2d(location, v.x, v.y); }
    inline void set_uniform(const glm::dvec3& v) const { glUniform3d(location, v.x, v.y, v.z); }
    inline void set_uniform(const glm::dvec4& v) const { glUniform4d(location, v.x, v.y, v.z, v.w); }
    inline void set_uniform(const glm::dmat4& v) const { glUniformMatrix4dv(location, 1, GL_FALSE, glm::value_ptr(v)); }
    inline void set_uniform(const uint32_t&   v) const { glUniform1ui(location, v); }
    inline void set_uniform(const glm::uvec2& v) const { glUniform2ui(location, v.x, v.y); }
    inline void set_uniform(const glm::uvec3& v) const { glUniform3ui(location, v.x, v.y, v.z); }
    inline void set_uniform(const glm::uvec4& v) const { glUniform4ui(location, v.x, v.y, v.z, v.w); }

private:
    unsigned int m_shaderID;
};


class Shader {
public:
    Shader(const std::string& vertex_source, const std::string& fragment_source);
    ~Shader(); 
    void bind() const;
    void unbind() const;
    
    template<typename T>
    bool set_uniform(const std::string& key, const T& value, const bool debug=false) {
        bool found = m_uniforms.find(key) != m_uniforms.end();
        if (!found) {
            if (debug) {
                printf("`%s` uniform doesnt exist!\n", key.c_str());
            }
            return false;
        }
        bind();
        m_uniforms[key].set_uniform(value);

        return found;
    }

private:
    std::unordered_map<std::string, UniformData> m_uniforms;
    int m_RendererID;
};
