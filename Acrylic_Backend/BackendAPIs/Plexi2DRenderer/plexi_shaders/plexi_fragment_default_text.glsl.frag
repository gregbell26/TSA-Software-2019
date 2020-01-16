#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 shared_textureCoords;

uniform vec4 color;
uniform sampler2D texture2D;

void main() {
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(texture2D, shared_textureCoords).r);

    out_color = color * sampled;
}