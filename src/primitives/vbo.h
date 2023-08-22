#ifndef VBO_H
#define VBO_H
#include "primitives.h"
#include "../utils/error_handling.h"

typedef struct VBO {
  GLuint id;
  GLint type;
} VBO;

VBO newVBO(GLint type);

void destroyVBO(VBO self);

void bindVBO(VBO self);

void VBOBuffer(VBO self, void* data, size_t offset, size_t count);

void unbindVBO(VBO self);

#endif
