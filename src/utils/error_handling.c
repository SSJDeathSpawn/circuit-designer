#include "error_handling.h"
#include<stdlib.h>

void getErrorAndLog(const char* file, const int line) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    fprintf(stderr, "Error! Something is gravely happened before %s at %d.\n", file, line);
    fprintf(stderr, "Error code: %x\n",err);
    exit(1);
  } 
}
