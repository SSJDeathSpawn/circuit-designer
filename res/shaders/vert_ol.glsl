//Vertex_outline.glsl
#version 330 core

layout (location=0) in vec2 pos;
layout (location=1) in vec4 colour;

out vData {
    smooth vec4 colour;
} vertex;

void main() {
    gl_Position = vec4(pos, 1.0f, 1.0f);
    vertex.colour = colour;
}