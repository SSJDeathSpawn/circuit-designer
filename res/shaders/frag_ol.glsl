//Fragment_outline.glsl
#version 330 core

in fData {
    smooth vec4 colour;
} frag;

void main() {
    gl_FragColor = frag.colour;
}