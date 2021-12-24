#ifndef SRC_SCENES_STARTSCENE_STARTSCENE_H_
#define SRC_SCENES_STARTSCENE_STARTSCENE_H_

#include "../Scene.h"

class StartScene: public Scene {
 public:
    int selected;

    StartScene();
    void drawScene();
    void drawSelected(bool dirUp);

 private:
    bool checkForSeedPacket();

    void runSelectedAction();
};

#endif  // SRC_SCENES_STARTSCENE_STARTSCENE_H_
