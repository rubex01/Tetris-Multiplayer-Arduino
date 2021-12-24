#ifndef SRC_SCENES_SCENE_H_
#define SRC_SCENES_SCENE_H_

class Scene {
 public:
    enum Constants {
        START_SCENE = 0,
        GAME_SCENE = 1,
        WIN_SCENE = 2,
        LOSE_SCENE = 3,
        LEADERBOARD_SCENE = 4
    };

    static void setScene(const Constants& scene);
    static void draw();
    static Scene* getCurrentScene();

    virtual void drawScene() = 0;

 private:
    static Scene* currentScene;
};

#endif  // SRC_SCENES_SCENE_H_
