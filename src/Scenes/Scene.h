#ifndef SRC_SCENES_SCENE_H_
#define SRC_SCENES_SCENE_H_

class Scene {
 public:
    enum Constants {
        START_SCENE = 0,
        GAME_SCENE = 1,
        WIN_SCENE = 2,
        LOSE_SCENE = 3
    };

    static void drawScene();
    static void setScene(const Constants& scene);
    static int getCurrentScene();
    static void draw();

 private:
    static int currentScene;
};

#endif  // SRC_SCENES_SCENE_H_
