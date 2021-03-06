#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/interrupt.h>
#include "Controller/Controller.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Scenes/GameScene/GameScene.h"
#include "Sound/NewTone.h"
#include "HighScore/HighScore.h"


int main() {
    sei();

    NewTone::initTimer2();
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
