#include "shader.h"

static void _log_and_fail(
    GLint handle, const char *adverb, const char *path,
    void (*getlog)(GLuint, GLsizei, GLsizei *, GLchar*),
    void (*getiv)(GLuint, GLenum, GLint *)) {
    GLint loglen;
    getiv(handle, GL_INFO_LOG_LENGTH, &loglen);

    char *logtext = calloc(1, loglen);
    getlog(handle, loglen, NULL, logtext);
    fprintf(stderr, "Error %s shader at %s:\n%s", adverb, path, logtext);

    free(logtext);
    exit(1);
}

static GLint _compile(char *path, GLenum type) {
    FILE *f;
    char *text;
    long len;

    f = fopen(path, "rb");
    if (f==NULL) {
        fprintf(stderr, "Error loading file %s\n", path);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    assert(len > 0);
    fseek(f, 0, SEEK_SET);
    text = calloc(1, len);
    assert(text != NULL);
    fread(text, 1, len, f);
    assert(strlen(text) > 0);
    fclose(f);

    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, (const GLchar* const*) &text, (const GLint*) &len);
    glCompileShader(id);


    GLint compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

    if (compiled == 0) {
        _log_and_fail(id, "compiling", path, glGetShaderInfoLog, glGetShaderiv);
        exit(1);
    }
    free(text);
    checkError();
    return id;
}

 
ShaderProgram createShader(char* vs_path, char* fs_path) {
  ShaderProgram self;
  self.vs_id = _compile(vs_path, GL_VERTEX_SHADER);
  self.fs_id = _compile(fs_path, GL_FRAGMENT_SHADER);
  self.gs_id = -1;
  self.id = glCreateProgram();

  glAttachShader(self.id, self.vs_id);
  glAttachShader(self.id, self.fs_id);

  glLinkProgram(self.id);

  GLint linked;
  glGetProgramiv(self.id, GL_LINK_STATUS, &linked);

  if (linked == 0) {
      char buf[512];
      snprintf(buf, 512, "[%s, %s]", vs_path, fs_path);
      printf("Error when linking shaders!\n");
      _log_and_fail(self.id, "linking", buf, glGetProgramInfoLog, glGetProgramiv);
      exit(1);
  }
  checkError();
  return self;
}

ShaderProgram createShaderWithGS(char* vs_path, char* fs_path, char* gs_path) {
    ShaderProgram self;
    self.vs_id = _compile(vs_path, GL_VERTEX_SHADER);
    self.fs_id = _compile(fs_path, GL_FRAGMENT_SHADER);
    self.gs_id = _compile(gs_path, GL_GEOMETRY_SHADER);
    self.id = glCreateProgram();

    glAttachShader(self.id, self.vs_id);
    glAttachShader(self.id, self.fs_id);
    glAttachShader(self.id, self.gs_id);

    glLinkProgram(self.id);

    GLint linked;
    glGetProgramiv(self.id, GL_LINK_STATUS, &linked);

    if (linked == 0) {
        char buf[512];
        snprintf(buf, 512, "[%s, %s]", vs_path, fs_path);
        printf("Error when linking shaders!\n");
        _log_and_fail(self.id, "linking", buf, glGetProgramInfoLog, glGetProgramiv);
        exit(1);
    }
    return self;
} 

void destroyShader(ShaderProgram self) {
  glDeleteProgram(self.id);
  glDeleteShader(self.vs_id);
  glDeleteShader(self.fs_id);
  if (self.gs_id != -1) {
      glDeleteShader(self.gs_id);
  }
  checkError();
}

void bindShader(ShaderProgram self) {
  glUseProgram(self.id);
  checkError();
}

void unbindShader() {
  glUseProgram(0);
  checkError();
}
