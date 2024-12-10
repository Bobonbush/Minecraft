#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoords;

out vec2 coords;
uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position =  model * vec4(aPos, 1.0);
    coords = aCoords;
}