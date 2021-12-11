#include "Display.h"
#include "SPI.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 Display::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void Display::init() {
    Display::tft.begin();
    Display::tft.fillScreen(ILI9341_BLACK);
}

void Display::fillCircle(int x, int y, int r, uint16_t c) {
    Display::tft.fillCircle(x, y, r, c);
}

void Display::drawCircle(int x, int y, int r, uint16_t c) {
    Display::tft.drawCircle(x, y, r, c);
}
