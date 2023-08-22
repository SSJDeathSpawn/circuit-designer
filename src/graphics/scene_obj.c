#include "scene_obj.h"

void freeSceneObj(SceneObject self) {
  if(self.shouldFree) {
    free(self.vert);
    free(self.ind);
  }
}
