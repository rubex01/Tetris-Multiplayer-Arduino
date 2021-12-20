#ifndef KBSMC_SRC_CONTROLLER_CONTROLLER_H_
#define KBSMC_SRC_CONTROLLER_CONTROLLER_H_

class Controller {
 public:
    static void init();
    static void update();
    static bool* getActions();

 private:
    static bool actionArray[6];
};

#endif  // KBSMC_SRC_CONTROLLER_CONTROLLER_H_
