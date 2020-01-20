#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 0) in vec2 in_textCoords;


out vec2 shared_textureCoords;

void main() {
    shared_textureCoords = in_textCoords.zw;

    gl_Position = vec4(in_position, 1.0f);
}