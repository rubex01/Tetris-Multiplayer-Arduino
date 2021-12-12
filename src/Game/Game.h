#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

class Game {
 public:
    static void init();
    static void startGame();
    static void startGame(int seed);
    static void endGame();

 private:
    static int gameSeed;

    static void setRandomSeed();
    static int generateRandomSeed();
};

#endif  // SRC_GAME_GAME_H_
