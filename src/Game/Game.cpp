#include "Game.h"
#include "../Display/Display.h"


void CreatePlayBorder(){
    for(int i = 300; i >= 80; i){
        Display::DrawTetrisBlock(0,i,GRAY);
        Display::DrawTetrisBlock(220,i,GRAY);
        i -= 20;
    }

    for(int i = 20; i<=200;i){
        Display::DrawTetrisBlock(i,80,GRAY);
        i+=20;
    }   
}

void Game::Init(){
    CreatePlayBorder();
    Display::DrawSmallTetrisBlok(30,35,GRAY);
    Display::DrawSmallTetrisBlok(40,35,GRAY);
    Display::DrawSmallTetrisBlok(30,45,GRAY);

    Display::DrawSmallTetrisBlok(190,35,GRAY);
    Display::DrawSmallTetrisBlok(190+10,35,GRAY);
    Display::DrawSmallTetrisBlok(190,45,GRAY);
    Display::DrawSmallTetrisBlok(190+10,45,GRAY);

    Display::DrawTetrisBlock(20,240,YELLOW);
    Display::DrawTetrisBlock(20,260,YELLOW);
    Display::DrawTetrisBlock(20,280,YELLOW);
    Display::DrawTetrisBlock(20,300,YELLOW);

    Display::DrawTetrisBlock(100,140,GREEN);
    Display::DrawTetrisBlock(120,140,GREEN);
    Display::DrawTetrisBlock(100,160,GREEN);
    Display::DrawTetrisBlock(120,160,GREEN);

    Display::DrawRect(10-1,10-1,62,62,0x2965);
    Display::DrawRect(10,10,60,60,0x2965);
    Display::FillRect(10,10,60,12,0x2965);
    Display::DrawText(29,13,1,"HOLD",ILI9341_WHITE);

    Display::DrawRect(170-1,10-1,62,62,0x2965);
    Display::DrawRect(170,10,60,60,0x2965);
    Display::FillRect(170,10,60,12,0x2965);
    Display::DrawText(188,13,1,"NEXT",ILI9341_WHITE);

    Display::DrawText(105,25,1,"Score:",ILI9341_WHITE);
    Display::DrawText(105,35,2,"560",ILI9341_WHITE);
}
