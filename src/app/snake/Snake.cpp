#include "Snake.h"

#define DISTANCE(x1, y1, x2, y2) \
   ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))

#define maxSnakeSize 1024

typedef struct {
    uint8_t x;
    uint8_t y;
} SnakeNode;

void Snake::run() {

    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();

    SnakeNode snakeNode[maxSnakeSize] = {{displayWidth / 2, displayHeight / 2}};
    uint16_t snakeIndex = 0;
    uint16_t step = 1; //每步大小 & 速度
    uint16_t score = 0;
    bool blink = true;
    bool newFood = true;
    SnakeNode food;
    food.x=displayWidth/2+40;
    food.y=displayHeight/2;
    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        u8g2.clearBuffer();
        for (int i = snakeIndex; i >= 0; --i) {
            u8g2.drawDisc(snakeNode[i].x++, snakeNode[i].y, 2);

        }
        if (DISTANCE(snakeNode[snakeIndex].x,snakeNode[snakeIndex].y,food.x,food.y)<9){
            snakeIndex++;
            snakeNode[snakeIndex]=snakeNode[snakeIndex-1];
            snakeNode[snakeIndex].x +=3;
            newFood= true;
        }


        if (newFood) {
//            food.x=getRandomNumber()%displayWidth;
//            food.y=getRandomNumber()%displayHeight;
            food.x=displayWidth/2 + 30;
            food.y=displayHeight/2;
            newFood= false;
        }

        if (blink){
            u8g2.drawDisc(food.x, food.y, 3);
        }
        blink=!blink;


        score = snakeIndex;
        u8g2.setColorIndex(1);
        u8g2.drawRBox(displayWidth / 4 * 3, 0,
                      displayWidth / 4 * 1, 12,
                      1);
        u8g2.setColorIndex(0);
        u8g2.printf(displayWidth / 4 * 3, 0, "%5d", score);
        u8g2.setColorIndex(1);

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


