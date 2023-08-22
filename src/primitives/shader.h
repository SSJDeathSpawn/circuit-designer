#ifndef SHADER_H
#define SHADER_H
#include "primitives.h"
#include "../utils/error_handling.h"

typedef struct ShaderProgram {
  GLuint id, vs_id, fs_id, gs_id;
} ShaderProgram;

#define SHADER_LAST SHADER_LINES
typedef enum ShaderEnum {
  SHADER_NONE=0,
  SHADER_BASIC,
  SHADER_LINES
} ShaderEnum;

ShaderProgram createShader(char* vs_path, char* fs_path);
ShaderProgram createShaderWithGS(char* vs_path, char* fs_path, char* gs_path);
void destroyShader(ShaderProgram self);
void bindShader(ShaderProgram self);
void unbindShader();

#endif // !SHADER_H
