#ifndef SRC_SCENES_WINSCENE_WINSCENE_H_
#define SRC_SCENES_WINSCENE_WINSCENE_H_

#include "../Scene.h"

class WinScene: public Scene {
 public:
    static void init();
    static void drawScene();
};

#endif  // SRC_SCENES_WINSCENE_WINSCENE_H_
