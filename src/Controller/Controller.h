#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

class Controller {
 public:
    enum Constants {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
        Z_BUTTON = 4,
        C_BUTTON = 5
    };

    static void init();
    static void update();
    static bool* getActions();
    static bool* getNonContinuingTriggerActions();

 private:
    static bool actionArray[6];
    static bool nonContinuingTrigger[6];

    static void updateStates();
};

#endif  // SRC_CONTROLLER_CONTROLLER_H_
