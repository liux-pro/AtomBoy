#include "FlappyBird.h"

#define pipeWidth (16)
#define pipeGap (40)


//每间隔多远有一个管子
#define pipeInterval (50)

// 管子y轴上下变化的最大值
#define pipeOffsetMax (24)

//鸟的x坐标恒定不变
#define BirdX (displayWidth / 8 * 1)


// 管子起始坐标


static void drawPipe(uint16_t x, uint8_t offset) {
    if (x > UINT8_MAX) { //超过u8g2绘制范围后不在绘制.
        return;
    }
    u8g2.drawBox(x - pipeWidth, (displayHeight / 2 + pipeGap / 2) + (offset - pipeOffsetMax / 2), pipeWidth, UINT8_MAX);
    u8g2.drawBox(x - pipeWidth, 0, pipeWidth, (displayHeight / 2 - pipeGap / 2) + (offset - pipeOffsetMax / 2));
}


static void drawBird(uint8_t y) {
    u8g2.drawDisc(displayWidth / 8 * 1, y, 4);
}

void FlappyBird::run() {
    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();
    uint32_t move = UINT32_MAX; //实际移动像素数的1024倍
    uint32_t moveScreen;  //实际屏幕像素
    uint32_t speed = 300;
    uint32_t lastX = 0;
    uint32_t birdY = displayHeight / 2 * 1024;
    uint32_t lastBirdY = displayHeight / 2;

    const uint32_t bird_v = 300;  // 速度
    const uint32_t bird_g = 4;   // 重力加速度
    uint32_t bird_t = 0;

    uint32_t score = 0;
    bool die = false;


    constexpr uint8_t pipeCount = (UINT8_MAX / pipeInterval);
    uint8_t Y_offset[pipeCount];  //管子的上下移动的偏移
    for (uint8_t &i: Y_offset) {
        i = getRandomNumber() % pipeOffsetMax;
    }
    //第一个管子在正中间,防止开始就死
    Y_offset[0] = pipeOffsetMax / 2;


    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();

        move = move - speed;
        moveScreen = move / 1024;

        u8g2.clearBuffer();

        //画管子
        uint32_t x = moveScreen % pipeInterval;
        if ((x == (pipeInterval - 1)) && (lastX == 0)) {  //一个新周期的开始
            for (int i = 0; i < pipeCount - 1; ++i) {
                Y_offset[i] = Y_offset[i + 1];
            }
            Y_offset[pipeCount - 1] = getRandomNumber() % pipeOffsetMax;
        }
        lastX = x;
        for (int i = 0; i < pipeCount; ++i) {
            drawPipe(i * pipeInterval + x, Y_offset[i]);
        }


        //画鸟(球)
        if (keyCheck(KEY_A)) {
            bird_t = 0;
            lastBirdY = (birdY / 1024) + lastBirdY;
        }
        birdY = -bird_v * bird_t + bird_g * bird_t * bird_t / 2;
        bird_t = bird_t + 3;
        uint16_t y = (birdY / 1024) + lastBirdY;
        drawBird(y);

        //判断游戏结束

        //撞上下边界
        if (y > displayHeight) {
            die = true;
        }
        //撞管子 (进入到管子之内)
        for (int i = 0; i < pipeCount; ++i) {
            if (BirdX > i * pipeInterval + x - pipeWidth && BirdX < i * pipeInterval + x) { //在两个管子之间夹着
                if (y < (displayHeight / 2 - pipeGap / 2) + (Y_offset[i] - pipeOffsetMax / 2)    //进到了上管子之内
                    || y > (displayHeight / 2 + pipeGap / 2) + (Y_offset[i] - pipeOffsetMax / 2)) { // 进到了下管子之内
                    die = true;
                }
            }
        }
        // 显示分数
        score = (UINT32_MAX - move) / 1024 / pipeInterval;
        u8g2.setColorIndex(1);
        u8g2.drawRBox(displayWidth / 4 * 3, 0,
                      displayWidth / 4 * 1, 12,
                      1);
        u8g2.setColorIndex(0);
        u8g2.printf(displayWidth / 4 * 3, 0, "%5d", score);
        u8g2.setColorIndex(1);


        u8g2.sendBuffer();
        if (die) {
            break;
        }
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


