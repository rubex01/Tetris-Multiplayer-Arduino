#include "Display.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 Display::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

uint16_t Display::colors[3][3] = {
    {0x7BEF,0xA534,0x4A69},
    {0xFF80,0xFFD0,0xEEE0},
    {0xB723,0xCF6D,0x9602}
    };

void Display::init(){
    
    Display::tft.begin();
    Display::tft.fillScreen(ILI9341_BLACK);
}

void Display::fillCircle(int x, int y, int r, uint16_t c){
    Display::tft.fillCircle(x,y,r,c);
}

void Display::drawCircle(int x, int y, int r, uint16_t c){
    Display::tft.drawCircle(x,y,r,c);
}

void Display::drawRect(int x, int y, int w, int h, uint16_t c){
    Display::tft.drawRect(x,y,w,h,c);
}

void Display::fillRect(int x, int y, int w, int h, uint16_t c){
    Display::tft.fillRect(x,y,w,h,c);
}

void Display::drawTetrisBlock(int x, int y, int color){
    // Draw main color block
    Display::fillRect(x,0+y,20,20,Display::colors[color][0]);

    // Draw outline
    Display::fillRect(x,y,20,3,0x2965);
    Display::fillRect(x,y,3,20,0x2965);
    Display::fillRect(x,17+y,20,3,0x2965);
    Display::fillRect(17+x,y,3,20,0x2965);

    // Draw light shdadow
    Display::fillRect(3+x,15+y,14,2,colors[color][1]);
    Display::fillRect(3+x+12,3+y,2,14,colors[color][1]);

    // Draw dark outline
    Display::fillRect(3+x,3+y,14,2,colors[color][2]);
    Display::fillRect(3+x,3+y,2,14,colors[color][2]);
}

void Display::drawSmallTetrisBlok(int x, int y, int c){
    // Draw main color
    Display::tft.fillRect(x,y,10,10,ILI9341_YELLOW);

    // Draw outline
    Display::tft.fillRect(x,y,10,1,	0x2965);
    Display::tft.fillRect(x,y,1,10,	0x2965);
    Display::tft.fillRect(x,9+y,10,1,	0x2965);
    Display::tft.fillRect(9+x,y,1,10,	0x2965);
}

void Display::drawText(int x, int y, int s, String t, uint16_t c){
    Display::tft.setCursor(x,y);
    Display::tft.setTextColor(c);
    Display::tft.setTextSize(s);
    Display::tft.setTextWrap(true);
    Display::tft.print(t);
}

void Display::drawGameBorder(){
    for(int i = 300; i >= 80; i){
        Display::drawTetrisBlock(0,i,GRAY);
        Display::drawTetrisBlock(220,i,GRAY);
        i -= 20;
    }

    for(int i = 20; i<=200;i){
        Display::drawTetrisBlock(i,80,GRAY);
        i+=20;
    }   
}

void Display::drawHoldSection(){
    Display::drawSmallTetrisBlok(30,35,GRAY);
    Display::drawSmallTetrisBlok(40,35,GRAY);
    Display::drawSmallTetrisBlok(30,45,GRAY);

    Display::drawRect(10-1,10-1,62,62,0x2965);
    Display::drawRect(10,10,60,60,0x2965);
    Display::fillRect(10,10,60,12,0x2965);
    Display::drawText(29,13,1,"HOLD",ILI9341_WHITE);
}

void Display::drawNextSection(){
    Display::drawSmallTetrisBlok(190,35,GRAY);
    Display::drawSmallTetrisBlok(190+10,35,GRAY);
    Display::drawSmallTetrisBlok(190,45,GRAY);
    Display::drawSmallTetrisBlok(190+10,45,GRAY);
    Display::drawRect(170-1,10-1,62,62,0x2965);
    Display::drawRect(170,10,60,60,0x2965);
    Display::fillRect(170,10,60,12,0x2965);
    Display::drawText(188,13,1,"NEXT",ILI9341_WHITE);
}

void Display::drawDemoBlocks(){
    Display::drawTetrisBlock(20,240,YELLOW);
    Display::drawTetrisBlock(20,260,YELLOW);
    Display::drawTetrisBlock(20,280,YELLOW);
    Display::drawTetrisBlock(20,300,YELLOW);

    Display::drawTetrisBlock(100,140,GREEN);
    Display::drawTetrisBlock(120,140,GREEN);
    Display::drawTetrisBlock(100,160,GREEN);
    Display::drawTetrisBlock(120,160,GREEN);
}

void Display::drawScore(){
    Display::drawText(105,25,1,"Score:",ILI9341_WHITE);
    Display::drawText(105,35,2,"560",ILI9341_WHITE);
}