#include "SpaceInvaders.h"
#include "app/common/Sprite.h"
#include "resource/IMAGE_spaceInvaders_alienA.h"
#include "resource/IMAGE_spaceInvaders_alienB.h"
#include "resource/IMAGE_spaceInvaders_alienC.h"
#include "resource/IMAGE_spaceInvaders_UFO.h"
#include "resource/IMAGE_spaceInvaders_user.h"

#define max(a, b) ((a > b) ? a : b)

typedef struct {
    uint8_t x;
    uint8_t y;
} Position;


static bool inBox(Position pos, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    return pos.x >= x && pos.x < x + width && pos.y >= y && pos.y < y + height;
}


void SpaceInvaders::run() {
    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();

    Sprite alienA(IMAGE_spaceInvaders_alienA_width, IMAGE_spaceInvaders_alienA_height, IMAGE_spaceInvaders_alienA,
                  IMAGE_spaceInvaders_alienA_maxStep, 30);
    Sprite alienB(IMAGE_spaceInvaders_alienB_width, IMAGE_spaceInvaders_alienB_height, IMAGE_spaceInvaders_alienB,
                  IMAGE_spaceInvaders_alienB_maxStep, 30);
    Sprite alienC(IMAGE_spaceInvaders_alienC_width, IMAGE_spaceInvaders_alienC_height, IMAGE_spaceInvaders_alienC,
                  IMAGE_spaceInvaders_alienC_maxStep, 30);
    Sprite UFO(IMAGE_spaceInvaders_UFO_width, IMAGE_spaceInvaders_UFO_height, IMAGE_spaceInvaders_UFO);
    Sprite user(IMAGE_spaceInvaders_user_width, IMAGE_spaceInvaders_user_height, IMAGE_spaceInvaders_user);

    Sprite *aliens[] = {
            &alienA,
            &alienB,
            &alienC
    };

    constexpr int numAliens = sizeof(aliens) / sizeof(aliens[0]);


    constexpr uint8_t maxWidth = max(max(IMAGE_spaceInvaders_alienA_width + 10, IMAGE_spaceInvaders_alienB_width + 10),
                                     IMAGE_spaceInvaders_alienC_width + 10);
    constexpr uint8_t line = displayWidth / maxWidth;
    bool alienAlive[line][numAliens];

    //可发射子弹的敌人的位置
    Position alienFireReadyPosition[line];
    //可发射子弹的敌人的数量
    uint8_t alienFireReadyCount = 0;


    for (auto &i: alienAlive) {
        for (bool &j: i) {
            j = true;
        }
    }


    Position userPosition;
    userPosition.x = displayWidth / 2 - user.width / 2;
    userPosition.y = displayHeight - user.height;

    uint8_t alienMove = 0;  // 敌人位置的偏移
    int8_t alienMoveStep = 1; //敌人移动方向

    Position bullet = {0xFF, 0xFF};
    Position bulletAlien = {0xFF, 0xFF}; //敌人发的子弹

    bool die= false;


    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        uint16_t keyStatus = ~keyScan();
        u8g2.clearBuffer();


        //控制敌人移动
        if (fps_get_frame() % 5 == 0) {// 每5帧变化一次
            alienMove += alienMoveStep;
        }
        if (alienMove >= displayWidth - maxWidth * line || alienMove <= 0) {
            alienMoveStep = -alienMoveStep;
        }

        //玩家移动
        if (checkBit(KEY_A_LEFT | KEY_B_LEFT, &keyStatus)) {
            if (userPosition.x > 0) {
                userPosition.x--;
            }
        }

        if (checkBit(KEY_A_RIGHT | KEY_B_RIGHT, &keyStatus)) {
            if (userPosition.x < displayWidth - 1) {
                userPosition.x++;
            }
        }
        user.draw(userPosition.x, userPosition.y);


        //玩家发射子弹
        if (keyCheck(KEY_A | KEY_B) && bullet.y > displayHeight /*屏幕中没有子弹才发能发射*/) {
            bullet.y = displayHeight - user.height;
            bullet.x = userPosition.x + user.width / 2;
        }
        //子弹移动
        if (bullet.y < displayHeight /*屏幕中有子弹*/) {
            bullet.y--;
            u8g2.drawDisc(bullet.x, bullet.y, 1);
            //碰撞检测
            for (int i = 0; i < displayWidth / maxWidth; ++i) {
                uint8_t offsetY = 1;
                for (int j = 0; j < numAliens; ++j) {
                    if (alienAlive[i][j]) {
                        const bool hit = inBox(bullet,
                                               alienMove + i * (maxWidth) + maxWidth / 2 - aliens[j]->width / 2,
                                               offsetY,
                                               aliens[j]->width, aliens[j]->height);
                        if (hit) {
                            alienAlive[i][j] = false;
                            bullet.x = 0xff;
                            bullet.y = 0xff;
                        }
                        offsetY = offsetY + aliens[j]->height + 1;
                    }
                }
            }
        }



        //敌人发射子弹
        if (bulletAlien.y >= displayHeight /*屏幕中没有子弹才发能发射*/
            and alienFireReadyCount > 0
                ) {
            uint8_t i = getRandomNumber() % alienFireReadyCount;
            bulletAlien = alienFireReadyPosition[i];
        }
        printf("%d\n",bulletAlien.y);
        //敌人子弹移动
        if (bulletAlien.y < displayHeight /*屏幕中有子弹*/) {
            bulletAlien.y++;
            u8g2.drawDisc(bulletAlien.x, bulletAlien.y, 1);
            //碰撞检测
            die = inBox(bulletAlien,
                                   userPosition.x,
                                   userPosition.y,
                                   user.width, user.height);
        }

        alienFireReadyCount = 0;
        // 绘制敌人
        for (int i = 0; i < line; ++i) {
            uint8_t offsetY = 1;
            bool anyAlien = false;
            for (int j = 0; j < numAliens; ++j) {
                if (alienAlive[i][j]) {
                    int xCenter = alienMove + i * (maxWidth) + maxWidth / 2;
                    aliens[j]->draw(xCenter - aliens[j]->width / 2, offsetY);
                    offsetY = offsetY + aliens[j]->height + 1;
                    ////////////////////////  维护可发射子弹的敌人的位置
                    anyAlien = true;
                    alienFireReadyPosition[alienFireReadyCount].x = xCenter;
                    alienFireReadyPosition[alienFireReadyCount].y = offsetY - 1;
                }
            }
            if (anyAlien) { alienFireReadyCount++; }
        }

        //游戏结束
        if (die){
            u8g2.setColorIndex(1);
            u8g2.drawBox(0,0,displayWidth,12);
            u8g2.setColorIndex(0);
            u8g2.printf(10,0,"Game Over");
            u8g2.sendBuffer();
            keyWaitAnyKey();
        }


        u8g2.sendBuffer();
    }

}
