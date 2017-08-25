#include "Arduino.h"

byte SnakeScreen[8] = {
    B00000000,
    B01111110,
    B01000000,
    B01111110,
    B00000010,
    B01011110,
    B00000000,
    B00000000};

byte PongScreen[8] = {
    B11110000,
    B00000000,
    B00000000,
    B00000100,
    B00000000,
    B00000000,
    B00000000,
    B00011110,};

byte FlappyScreen[8] = {
    B00000110,
    B00000110,
    B00000000,
    B00000000,
    B00000000,
    B01000110,
    B00000110,
    B00000110,
};

byte NameScreen[8] = {
    B00111100,
    B01100110,
    B11000110,
    B00001100,
    B00011000,
    B00000000,
    B00011000,
    B00011000};

byte SpaceInvadersScreen[8] = {
    B01110011,
    B00001011,
    B11000011,
    B11000000,
    B00001000,
    B00000000,
    B00001000,
    B00011100};

byte BreakoutScreen[8] = {
    B11111111,
    B11111111,
    B11000111,
    B11000000,
    B00000000,
    B00000010,
    B00000000,
    B00111000
};

byte SimonScreen[8] = {
    B00000000,
    B00011000,
    B00111100,
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00000000};

byte TRScreen[8] = {
    B11111000,
    B00100000,
    B00100000,
    B00101110,
    B00101001,
    B00001110,
    B00001001,
    B00001001};

byte STScreen[8] = {
    B00000000,
    B00000100,
    B00000100,
    B00001100,
    B00011100,
    B00111100,
    B01111100,
    B01111110,
};

void showScreen(int screen) {
    switch (screen) {
        case SNAKE:
            gamer.printImage(SnakeScreen);
            break;
        case FLAPPY:
            gamer.printImage(FlappyScreen);
            break;
        case PONG:
            gamer.printImage(PongScreen);
            break;
        case NAME:
            gamer.printImage(NameScreen);
            break;
        case SPACE_INVADERS:
            gamer.printImage(SpaceInvadersScreen);
            break;
        case BREAKOUT:
            gamer.printImage(BreakoutScreen);
            break;
        case SIMON:
            gamer.printImage(SimonScreen);
            break;
        case TEMPLE_RUN:
            gamer.printImage(TRScreen);
            break;
        case STACKER:
            gamer.printImage(STScreen);
            break;
    }
}

