#ifndef SRC_SCENES_WINSCENE_WINSCENE_H_
#define SRC_SCENES_WINSCENE_WINSCENE_H_

#include "../Scene.h"

class WinScene: public Scene {
 public:
    int titleAnimationCounter;
    int titleColorAnimationCounter;
    int continueAnimationCounter;

    WinScene();
    void drawScene();
    void titleTextAnimation();
    void titleColorAnimation();
    void continueTextAnimation();
};

#endif  // SRC_SCENES_WINSCENE_WINSCENE_H_
