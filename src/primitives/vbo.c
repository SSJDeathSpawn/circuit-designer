#include "vbo.h"


VBO newVBO(GLint type) {
    VBO self = {
        .type=type
    };
    glGenBuffers(1, &self.id);
    checkError();
    return self;
}

void destroyVBO(VBO self) {
  glDeleteBuffers(1, &self.id);
    checkError();
}

void bindVBO(VBO self) {
  glBindBuffer(self.type, self.id);
  checkError();
}

void VBOBuffer(VBO self, void* data, size_t offset, size_t count) {
    bindVBO(self);
    glBufferData(self.type, count - offset, data, GL_DYNAMIC_DRAW);
    checkError();
}

void unbindVBO(VBO self) {
  glBindBuffer(self.type, 0);
  checkError();
}
