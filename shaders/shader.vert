
#version 450 core
layout(location=0) in vec3 in_vert;
layout(location=1) in vec2 in_textCoord;

layout(location=0) out vec2 out_textCoord;

// model view projection
uniform mat4 iMVP;

void main() {
    gl_Position = iMVP * vec4(in_vert, 1.0);
    out_textCoord = in_textCoord;
}
