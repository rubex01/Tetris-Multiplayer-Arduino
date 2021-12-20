#ifndef KBSMC_SRC_SCENES_STARTSCENE_STARTSCENE_H_
#define KBSMC_SRC_SCENES_STARTSCENE_STARTSCENE_H_

#include "../Scene.h"

class StartScene: public Scene {
 public:
    static int selected;

    static void init();
    static void drawScene();
    static void drawSelected(bool dirUp);

 private:
    static bool checkForSeedPacket();
};

#endif  // KBSMC_SRC_SCENES_STARTSCENE_STARTSCENE_H_
