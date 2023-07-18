#include "Dino.h"
#include "app/common/Sprite.h"
#include "app/dino/resource/IMAGE_dino_dino.h"
#include "app/dino/resource/IMAGE_dino_bird.h"
#include "app/dino/resource/IMAGE_dino_treeA.h"
#include "app/dino/resource/IMAGE_dino_treeB.h"
#include "utils.h"

#define DISTANCE(x1, y1, x2, y2) \
   ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))

void Dino::run() {
    Sprite dino(IMAGE_dino_dino_width, IMAGE_dino_dino_height, IMAGE_dino_dino, IMAGE_dino_dino_maxStep, 4);
    Sprite bird(IMAGE_dino_bird_width, IMAGE_dino_bird_height, IMAGE_dino_bird, IMAGE_dino_bird_maxStep, 8);
    Sprite treeA(IMAGE_dino_treeA_width, IMAGE_dino_treeA_height, IMAGE_dino_treeA);
//    Sprite treeB(IMAGE_dino_treeB_width, IMAGE_dino_treeB_height, IMAGE_dino_treeB);
    u8g2.setFontPosTop();
    u8g2.setColorIndex(1);
    uint8_t speed = 1;
    constexpr uint8_t roadDecoration = 5;
    int32_t move = 0;
    int32_t jumpTime = 0;   // 时间变量
    constexpr int32_t jumpGravity = -4;    //重力加速度
    constexpr int32_t jumpVelocity = 550;  //起跳的初速度
    int32_t jumpDistance = 0;    //跳起的高度
    bool jumping = false;    // 是否正在跳跃,在半空中
    uint8_t changeFlag = 0;
    uint32_t blocker = 0;   //障碍物出现的位置坐标
    uint32_t score = 0;

    const auto dinoX = displayWidth / 4 * 1;


    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        u8g2.clearBuffer();

        //屏幕匀速滚动.
        move = move + speed;

        // 绘制地面
        u8g2.drawLine(0, displayHeight / 8 * 7, displayWidth, displayHeight / 8 * 7);
        // 绘制地面上的点点
        for (int i = 1; i < roadDecoration + 1; ++i) {
            u8g2.drawLine(-move % (displayWidth / roadDecoration) + displayWidth / roadDecoration * i,
                          displayHeight / 8 * 7 + 5,
                          -move % (displayWidth / roadDecoration) + displayWidth / roadDecoration * i + 4,
                          displayHeight / 8 * 7 + 5);
        }

        // 跳跃
        if (keyCheck(KEY_A) && !jumping) {
            jumping = true;
        }
        if (jumping) {
            jumpTime = jumpTime + 4 + speed;
            jumpDistance = jumpVelocity * jumpTime + jumpGravity * jumpTime * jumpTime / 2;
            if (jumpDistance < 0) {
                jumping = false;
                jumpTime = 0;
                jumpDistance = 0;
            }
        }
        int32_t dinoY = displayHeight / 8 * 7 - IMAGE_dino_dino_height - (jumpDistance / 1024);
        dino.draw(dinoX, dinoY);

        //绘制鸟或者树
        uint32_t x = blocker - move;
        uint32_t y = 0;
        if (changeFlag % 2 == 0) {
            //树
            y = displayHeight / 8 * 7 - IMAGE_dino_treeA_height;
            treeA.draw(x, y);
        } else if (changeFlag % 2 == 1) {
            // 鸟
            y = displayHeight / 8 * 3 - IMAGE_dino_bird_height;
            bird.draw(x, y);
        }
        //判断是否有碰撞.
        if (DISTANCE(x, y, dinoX, dinoY) < 100) {  //不用那么准确
            break;
        }
        if (x > 0xff) {  //如果blocker - move为负数,考虑到x是uint32,只要x>0xff就是负数了
            blocker = move + getRandomNumber() % (displayWidth / 2) + displayWidth; //下个树或鸟出现在当前位置+随机距离+屏幕宽度的位置.
            changeFlag = getRandomNumber();  // 决定了下个出现是是鸟还是树
        }

        score = move / 10;
        u8g2.printf(64, 6, "score:%d", move / 10);
        speed = (score / 100) + 1;

        u8g2.sendBuffer();
    }
    //走到这里就已经死了.
    //绘制计分板
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
