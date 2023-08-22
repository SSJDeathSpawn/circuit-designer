#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices=3) out;

in vData {
    smooth vec4 colour;
} vertices[];

out fData {
    smooth vec4 colour;
} frag;

void main() {
    
    for(int i=0;i<3;i++) {
        frag.colour = vertices[i].colour; 
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }

    EndPrimitive();
}