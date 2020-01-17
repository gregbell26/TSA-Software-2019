#version 330 core

layout(location = 0) in vec4 in_allCoords;

uniform mat4 viewProjection;

out vec2 shared_textureCoords;

void main() {
    shared_textureCoords = in_allCoords.zw;

    gl_Position = viewProjection * vec4(in_allCoords.xy, 1.0f, 1.0f);//By default we are just gonna put text on top of everything
}