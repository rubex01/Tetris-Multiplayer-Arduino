#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Display.h"


class Display {
	public:
        static void Init();
        static void FillCircle(int x, int y,int r, uint16_t c);
        static Adafruit_ILI9341 tft;
	private:

};


#endif
