#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "primitives/shader.h"
#include "primitives/vao.h"
#include "graphics/renderer.h"
#include "graphics/scene_obj.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT; 
static GLFWwindow *window = NULL;

static void glfw_die(const char * message) {
  fprintf(stderr, "%s\n", message);
  exit(2);
}

void init_screen(const char* title) {
  if(!glfwInit()) {
    glfw_die("Couldn't initialize GLFW");
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, NULL, NULL);
  glfwMakeContextCurrent(window);

  if(window == NULL) glfw_die("Could not initialize window");

  printf("OpenGL Loaded\n");
  int version = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version:  %s\n", glGetString(GL_VERSION));
  
  glfwSwapInterval(1);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(void) {
  init_screen("Circuit Designer");

  VertexLayout *vl;
  vl = (VertexLayout *) malloc(sizeof(VertexLayout) + 2 * sizeof(GLint));
  vl->counter = 0;
  vl->stride = 0;
  addElementVL(vl, 2);
  addElementVL(vl, 4);
  
  Renderer renderer;

  initRenderer(&renderer);
  
  Vertex vertices[4] = {
    {{ -0.5f, -0.5f},{1.0f, 1.0f, 1.0f, 0.0f}}, 
    {{  0.5f, -0.5f},{1.0f, 1.0f, 1.0f, 0.0f}},
    {{  0.5f, 0.5f},{1.0f, 1.0f, 1.0f, 0.0f}},
    {{  -0.5f, 0.5f},{1.0f, 1.0f, 1.0f, 0.0f}}
  };
  
  GLuint indices[] = {
    0, 1, 2, 
    2, 3, 0
  };

  SceneObject rectangle = {
    .shader = SHADER_LINES,
    .vert = vertices,
    .num_vertices = sizeof(vertices)/sizeof(Vertex), 
    .ind = indices,
    .num_indices = sizeof(indices)/sizeof(GLuint),
    .noInd = false,
    .shouldFree = false
  };

  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    loadSceneObjRenderer(&renderer, rectangle);
    loadVAOAttrs(renderer, vl);
    drawCallRenderer(renderer, GL_TRIANGLES);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);

  free(vl);
  destroyRenderer(&renderer);
  glfwTerminate();
  return 0;
}
