#ifndef SRC_SCENES_WINSCENE_WINSCENE_H_
#define SRC_SCENES_WINSCENE_WINSCENE_H_

#include "../Scene.h"

class WinScene: public Scene {
 public:
    static int titleAnimationCounter;
    static int titleColorAnimationCounter;
    static int continueAnimationCounter;

    static void init();
    static void drawScene();
    static void titleTextAnimation();
    static void titleColorAnimation();
    static void continueTextAnimation();
};

#endif  // SRC_SCENES_WINSCENE_WINSCENE_H_
