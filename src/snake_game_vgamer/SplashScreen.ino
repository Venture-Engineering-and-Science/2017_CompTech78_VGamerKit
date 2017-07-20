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
    B11101110,
    B10001001,
    B10001001,
    B11101111,
    B10001001,
    B10001001,
    B10001110,
    B00000000};

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
    B00110000,
    B00000110,
    B11000110,
    B11000000,
    B00001000,
    B00000000,
    B00001000,
    B00011100};


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
    }
}

