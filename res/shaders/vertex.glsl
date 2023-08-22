#version 330 core

layout (location=0) in vec2 pos;
layout (location=1) in vec4 col;

smooth out vec4 colour;

void main() {
    gl_Position = vec4(pos,1.0f, 1.0f);
    colour = col;
}
