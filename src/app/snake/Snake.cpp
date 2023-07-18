#include "Snake.h"




void Snake::run() {
    uint8_t step = 1; //每步大小 & 速度



    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();
    uint16_t score = 0;
    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        u8g2.clearBuffer();

        u8g2.sendBuffer();
    }
    u8g2.drawRBox(displayWidth / 8 * 1, displayHeight / 8 * 1,
                  displayWidth / 8 * 6, displayHeight / 8 * 6,
                  5);
    u8g2.setColorIndex(0);
    u8g2.printf(displayWidth / 8 * 2 + 3, displayHeight / 8 * 2 - 5, "Game Over", score);

    u8g2.printf(displayWidth / 8 * 2 + 3, displayHeight / 8 * 3, "score:%5d", score);
    u8g2.printf(displayWidth / 8 * 2 + 3, displayHeight / 8 * 4 + 5, "score:%5d", score);
    u8g2.sendBuffer();

    keyWaitAnyKey();

}


