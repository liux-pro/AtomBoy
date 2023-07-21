#pragma once

#include "../common/Application.h"
#include "app/common/Sprite.h"

class Gomoku : Application {
private:
    Sprite *white{};
    Sprite *black{};
    void drawPiece(uint8_t x, uint8_t y, int8_t piece);

public:
    void run() override;

    void drawWinLine(int x, int y);
};
