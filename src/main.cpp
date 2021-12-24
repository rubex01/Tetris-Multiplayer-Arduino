#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include <avr/interrupt.h>
#include "Controller/Controller.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Scenes/GameScene/GameScene.h"
#include "Communication/ReceivedData.h"
#include "Sound/NewTone.h"
#include "Communication/Frame.h"
#include "HighScore/HighScore.h"

// #define ONESECOND 15  // Timer2 15 goeie, 1024 pre met ovf
#define ONESECOND 20  // Timer2 15 goeie, 1024 pre met COMPA zonder pauze


int main() {
    NewTone::initTimer2();
    sei();

    Controller::init();
    Display::init();
    HighScore::init();
    Scene::setScene(Scene::START_SCENE);

    IRCommunication::init(38);

    while (true) {
        Controller::update();
        Scene::draw();
        if (NewTone::startTone) {
            if (NewTone::toggleTone) {
                NewTone::toggleTone = false;
                NewTone::playTone();
            }
        }
    }
    return(0);
}
