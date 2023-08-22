#ifndef RENDERER_H
#define RENDERER_H
#include "../primitives/vao.h"
#include "../primitives/vbo.h"
#include "../primitives/shader.h"
#include "scene_obj.h"
#include "../utils/basic.h"
#include "../utils/error_handling.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Renderer {
    VBO curr_vbo, curr_ibo;
    VAO curr_vao;    
    ShaderProgram all_shaders[SHADER_LAST+1];
    ShaderEnum curr_shader; 
    ShaderProgram sel_shader;
    bool flag;
    GLuint points;
} Renderer;

void initRenderer(Renderer* self);
void destroyRenderer(Renderer* self);
void loadVIRenderer(Renderer *self, Vertex vertices[], int num_vertices, GLuint indices[], int num_indices);
void loadVRenderer(Renderer *self, Vertex vertices[], int num_vertices);
void loadSceneObjRenderer(Renderer *self, SceneObject scene_obj);
void useShaderRenderer(Renderer *self, ShaderEnum shader);
void drawCallRenderer(Renderer self, GLenum mode);
void loadVAOAttrs(Renderer self, VertexLayout *vl);

#endif
