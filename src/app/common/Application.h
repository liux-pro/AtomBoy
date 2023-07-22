#pragma once
#define APPLICATION_MENU 0
#define APPLICATION_DINO 1
#define APPLICATION_FLAPPY_BIRD 2
#define APPLICATION_SNAKE 3
#define APPLICATION_GOMOKU 4
#define APPLICATION_2048 5
#define APPLICATION_SPACE_INVADERS 6

#define APPLICATION_DEFAULT APPLICATION_GOMOKU


#include "button.h"
#include "Arduino.h"
#include "fps/fps.h"
#include "utils.h"

extern uint8_t nextApplication;

class Application {
public:
    virtual void run() = 0;
};