#ifndef SRC_SCENES_LOSESCENE_LOSESCENE_H_
#define SRC_SCENES_LOSESCENE_LOSESCENE_H_

#include "../Scene.h"

class LoseScene: public Scene {
 public:
    static int continueAnimationCounter;
    static int titleAnimationCounter;

    static void init();
    static void drawScene();
    static void continueTextAnimation();
    static void titleTextAnimation();
    static void resetHighScores();
};

#endif  // SRC_SCENES_LOSESCENE_LOSESCENE_H_
