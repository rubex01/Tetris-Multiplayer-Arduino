#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Display.h"

#define GRAY 0
#define YELLOW 1
#define GREEN 2


class Display {
	public:
        static void Init();
        static uint16_t colors[3][3];
        static void FillCircle(int x, int y,int r, uint16_t c);
        static void DrawCircle(int x, int y, int r, uint16_t c);
        static void FillRect(int x, int y,int w, int h, uint16_t c);
        static void DrawRect(int x, int y, int w, int h, uint16_t c);
        static void DrawTetrisBlock(int x, int y, int c);
        static void DrawSmallTetrisBlok(int x, int y, int c);
        static void DrawText(int x, int y, int s, String t, uint16_t c);
        static Adafruit_ILI9341 tft;
	private:

};


#endif
