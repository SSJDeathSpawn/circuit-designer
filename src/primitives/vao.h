#ifndef VAO_H
#define VAO_H

#include "primitives.h"
#include "vbo.h"
#include "../utils/error_handling.h"

typedef struct VertexLayout {
  int counter;
  GLsizei stride;
  GLint sizes[];
} VertexLayout ;

typedef struct VAO {
  GLuint id;
} VAO;

VAO newVAO();
void addElementVL(VertexLayout* self, GLint size);
void destroyVAO(VAO self);
void bindVAO(VAO self);
void unbindVAO();
void attrVAO(VAO self, VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);
void addAttrVLVAO(VAO self, VBO vbo, VertexLayout *vl);

#endif // !VAO_H
