#include "Display.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 Display::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

uint16_t Display::colors[3][3] = {
    {0x7BEF,0xA534,0x4A69},
    {0xFF80,0xFFD0,0xEEE0},
    {0xB723,0xCF6D,0x9602}
    };

void Display::Init(){
    
    Display::tft.begin();
    Display::tft.fillScreen(ILI9341_BLACK);
}

void Display::FillCircle(int x, int y, int r, uint16_t c){
    Display::tft.fillCircle(x,y,r,c);
}

void Display::DrawCircle(int x, int y, int r, uint16_t c){
    Display::tft.drawCircle(x,y,r,c);
}

void Display::DrawRect(int x, int y, int w, int h, uint16_t c){
    Display::tft.drawRect(x,y,w,h,c);
}

void Display::FillRect(int x, int y, int w, int h, uint16_t c){
    Display::tft.fillRect(x,y,w,h,c);
}

void Display::DrawTetrisBlock(int x, int y, int color){
    // Draw main color block
    Display::FillRect(x,0+y,20,20,Display::colors[color][0]);

    // Draw outline
    Display::FillRect(x,y,20,3,0x2965);
    Display::FillRect(x,y,3,20,0x2965);
    Display::FillRect(x,17+y,20,3,0x2965);
    Display::FillRect(17+x,y,3,20,0x2965);

    // Draw light shdadow
    Display::FillRect(3+x,15+y,14,2,colors[color][1]);
    Display::FillRect(3+x+12,3+y,2,14,colors[color][1]);

    // Draw dark outline
    Display::FillRect(3+x,3+y,14,2,colors[color][2]);
    Display::FillRect(3+x,3+y,2,14,colors[color][2]);
}

void Display::DrawSmallTetrisBlok(int x, int y, int c){
    // Draw main color
    Display::tft.fillRect(x,y,10,10,ILI9341_YELLOW);

    // Draw outline
    Display::tft.fillRect(x,y,10,1,	0x2965);
    Display::tft.fillRect(x,y,1,10,	0x2965);
    Display::tft.fillRect(x,9+y,10,1,	0x2965);
    Display::tft.fillRect(9+x,y,1,10,	0x2965);
}

void Display::DrawText(int x, int y, int s, String t, uint16_t c){
    Display::tft.setCursor(x,y);
    Display::tft.setTextColor(c);
    Display::tft.setTextSize(s);
    Display::tft.setTextWrap(true);
    Display::tft.print(t);
}