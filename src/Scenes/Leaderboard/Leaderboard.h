#ifndef SRC_SCENES_LOSESCENE_LEADERBOARD_H_
#define SRC_SCENES_LOSESCENE_LEADERBOARD_H_

#include "../Scene.h"

class Leaderboard : public Scene {
 public:
    Leaderboard();
    void drawScene();

 private:
    void drawLeaderboard();
};

#endif  // SRC_SCENES_LOSESCENE_LEADERBOARD_H_
