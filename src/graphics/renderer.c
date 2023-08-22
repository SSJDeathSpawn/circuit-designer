#include "renderer.h"
#include <glad/glad.h>

void initRenderer(Renderer *self) {
    *self = (Renderer) {0};
    self->curr_shader = SHADER_NONE;

    self->all_shaders[SHADER_BASIC] = createShader("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    self->all_shaders[SHADER_LINES] = createShaderWithGS("res/shaders/vert_ol.glsl", "res/shaders/frag_ol.glsl", "res/shaders/lines.glsl");
  
    self->curr_vao = newVAO();
    self->curr_vbo = newVBO(GL_ARRAY_BUFFER);
    self->curr_ibo = newVBO(GL_ELEMENT_ARRAY_BUFFER);
    self->flag = false;
}

void destroyRenderer(Renderer *self) {
  for (size_t i =0;i<=SHADER_LAST;i++) {
      destroyShader(self->all_shaders[i]);
  }
  destroyVAO(self->curr_vao);
  destroyVBO(self->curr_vbo);
  destroyVBO(self->curr_ibo);
}

void loadVIRenderer(Renderer *self, Vertex vertices[], int num_vertices, GLuint indices[], int num_indices) {
    self->flag = true;
    VBOBuffer(self->curr_vbo, vertices, 0, sizeof(vertices[0])*num_vertices);
    VBOBuffer(self->curr_ibo, indices, 0, sizeof(indices[0])*num_indices);
    self->points = num_indices;
}

void loadVRenderer(Renderer* self, Vertex vertices[], int num_vertices) {
    self->flag = false;
    VBOBuffer(self->curr_vbo, vertices, 0, sizeof(vertices[0])*num_vertices);
    self->points = num_vertices;
}

void loadSceneObjRenderer(Renderer *self, SceneObject scene_obj) {
    if(!scene_obj.noInd) {
        loadVIRenderer(self, scene_obj.vert, scene_obj.num_vertices, scene_obj.ind, scene_obj.num_indices);
    } else {
        loadVRenderer(self, scene_obj.vert, scene_obj.num_vertices);
    }
    useShaderRenderer(self, scene_obj.shader);
}

void useShaderRenderer(Renderer *self, ShaderEnum shader) {
    if(shader == self->curr_shader) {
        return;
    }
    self->curr_shader = shader;
    self->sel_shader = self->all_shaders[shader];
    bindShader(self->sel_shader);
}

void drawCallRenderer(Renderer self, GLenum mode) {
    bindVAO(self.curr_vao);
    bindVBO(self.curr_vbo);
    if (self.flag) {
        bindVBO(self.curr_ibo);
        glDrawElements(mode, self.points, GL_UNSIGNED_INT, (void* ) 0);
        unbindVBO(self.curr_ibo);
    } else {
        glDrawArrays(mode, 0, self.points);
    }
}

void loadVAOAttrs(Renderer self, VertexLayout *vl) {
    addAttrVLVAO(self.curr_vao, self.curr_vbo, vl);
}
