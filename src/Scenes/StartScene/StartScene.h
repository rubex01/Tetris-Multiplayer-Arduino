#ifndef SRC_SCENES_STARTSCENE_STARTSCENE_H_
#define SRC_SCENES_STARTSCENE_STARTSCENE_H_

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

#endif  // SRC_SCENES_STARTSCENE_STARTSCENE_H_
