#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <avr/io.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Arduino.h>
#include "Nunchuk.h"

class Controller {
	public:
        static void Init();
        static void Update();
	private:

};


#endif
