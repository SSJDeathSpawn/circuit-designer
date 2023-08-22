#include "vao.h"

VAO newVAO() {
  VAO self;
  glGenVertexArrays(1, &self.id);
  return self;
  checkError();
}

void addElementVL(VertexLayout* self, GLint size) {
  self->sizes[self->counter++] = size;
  self->stride += sizeof(GLfloat) * size;
}

void destroyVAO(VAO self) {
  glDeleteVertexArrays(1, &self.id);
  checkError();
}

void bindVAO(VAO self) {
  glBindVertexArray(self.id);
  checkError();
}

void attrVAO(VAO self, VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) {
    bindVAO(self);
    bindVBO(vbo);
    glEnableVertexAttribArray(index);
    switch(type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(index, size, type, stride, (void *) offset);
            break;
        default:
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *) offset);
            break; 
    }
  checkError();
}

void addAttrVLVAO(VAO self, VBO vbo, VertexLayout *vl) {
  int offset = 0;
  for(int i=0;i<vl->counter;i++) {
      attrVAO(self, vbo, i, vl->sizes[i], GL_FLOAT, vl->stride, offset);
      offset += vl->sizes[i] * sizeof(GLfloat);
  }
  checkError();
}
