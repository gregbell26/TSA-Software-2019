#version 330 core

layout(location = 0) in vec3 in_positionCoords;
layout(location = 1) in vec2 in_textureCoords;

uniform mat4 viewProjection;
uniform mat4 transform;

out vec2 shared_textureCoords;

void main()
{
    shared_textureCoords = in_textureCoords;
    gl_Position = viewProjection * transform * vec4(in_positionCoords, 1.0);
}
