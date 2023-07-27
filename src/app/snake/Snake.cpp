#include "Snake.h"

#define DISTANCE(x1, y1, x2, y2) \
   ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))

#define maxSnakeSize 1024
// 两个蛇间距
#define D 3

typedef struct {
    uint8_t x;
    uint8_t y;
} SnakeNode;

void Snake::run() {

    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();

    SnakeNode snakeNode[maxSnakeSize] = {{20, displayHeight / 2}};
    uint16_t snakeIndex = 0;
    int8_t moveX = 1;  //x方向速度
    int8_t moveY = 0;  //y方向速度

    bool die = false;

    uint16_t score = 0;
    bool blink = true;
    uint8_t blinkCount = 0;
    bool newFood = true;
    SnakeNode food;
    food.x = displayWidth / 2 + 40;
    food.y = displayHeight / 2;

    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        u8g2.clearBuffer();


        if (keyCheck(KEY_AB_UP)) {
            moveX = 0;
            moveY = -1;
        }
        if (keyCheck(KEY_AB_DOWN)) {
            moveX = 0;
            moveY = 1;
        }
        if (keyCheck(KEY_AB_LEFT)) {
            moveY = 0;
            moveX = -1;
        }
        if (keyCheck(KEY_AB_RIGHT)) {
            moveY = 0;
            moveX = 1;
        }


        snakeNode[snakeIndex].x += moveX;
        snakeNode[snakeIndex].y += moveY;

        for (int i = 0; i < snakeIndex; ++i) {
            snakeNode[i] = snakeNode[i + 1];
        }

        for (int i = 0; i < snakeIndex + 1; ++i) {
            u8g2.drawDisc(snakeNode[i].x, snakeNode[i].y, 2);
        }


        if (DISTANCE(snakeNode[snakeIndex].x, snakeNode[snakeIndex].y, food.x, food.y) < 16) {
            snakeIndex++;
            snakeNode[snakeIndex] = snakeNode[snakeIndex - 1];
            snakeNode[snakeIndex].x += moveX > 0 ? 1 : (moveX < 0 ? -1 : 0);
            snakeNode[snakeIndex].y += moveY > 0 ? 1 : (moveY < 0 ? -1 : 0);
            newFood = true;
        }


        if (newFood) {
            food.x = getRandomNumber() % (displayWidth - 10) + 5;  // -10 避免墙距离太近
            food.y = getRandomNumber() % (displayHeight - 10) + 5;
            newFood = false;
        }

        if (blink) {
            u8g2.drawDisc(food.x, food.y, 3);
        } else {
            u8g2.drawCircle(food.x, food.y, 3);
        }
        if (blinkCount++ % 10 == 0) {
            blink = !blink;
        }


        if (snakeNode[snakeIndex].x > displayWidth || snakeNode[snakeIndex].y > displayHeight) {
            die = true;
        }


        score = snakeIndex;
        u8g2.setColorIndex(1);
        u8g2.drawRBox(displayWidth / 4 * 3, 0,
                      displayWidth / 4 * 1, 12,
                      1);
        u8g2.setColorIndex(0);
        u8g2.printf(displayWidth / 4 * 3, 0, "%5d", score);
        u8g2.setColorIndex(1);

        u8g2.sendBuffer();

        if (die){
            break;
        }
    }

    u8g2.setColorIndex(1);

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



