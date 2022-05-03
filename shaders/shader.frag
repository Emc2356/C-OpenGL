#version 450 core
#ifdef GL_ES
precision mediump float;
#endif

layout(location=0) in vec2 textCoord;

out vec4 FragColor;

uniform int iWidth;
uniform int iHeight;
uniform float iTime;
uniform sampler2D iTexture;

void main() {
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // FragColor = vec4(1.0, (sin(iTime) + 1) / 2, (sin(iTime + 0.5) + 1) / 2, 1.0);
    FragColor = texture(iTexture, textCoord);
    // FragColor = vec4(1.0f);
}
