#ifndef SRC_SCENES_LOSESCENE_LOSESCENE_H_
#define SRC_SCENES_LOSESCENE_LOSESCENE_H_

#include "../Scene.h"

class LoseScene: public Scene {
 public:
    int continueAnimationCounter;
    int titleAnimationCounter;

    LoseScene();
    void drawScene();

 private:
    void continueTextAnimation();
    void titleTextAnimation();
};

#endif  // SRC_SCENES_LOSESCENE_LOSESCENE_H_
