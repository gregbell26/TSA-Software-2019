#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 shared_textureCoords;

uniform sampler2D texture2D;


void main() {
    out_color = texture(texture2D, shared_textureCoords);
}