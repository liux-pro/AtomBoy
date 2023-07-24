#include "Game2048.h"

#define girdWidth (displayWidth/4)
#define girdHeight (displayHeight/4)


static void drawGird() {
    for (int i = 1; i < 4; ++i) {
        u8g2.drawLine(i * girdWidth, 0, i * girdWidth, displayHeight);
        u8g2.drawLine(0, i * girdHeight, displayWidth, i * girdHeight);
    }
}

static void draw(uint8_t x, uint8_t y, uint32_t num) {
    if (num != 0) {
        u8g2.setFontPosCenter();
        char buffer[10];
        snprintf(buffer, sizeof(buffer), "%d", num);  // 使用 vsnprintf 将格式化的字符串写入缓冲区
        u8g2_uint_t width = u8g2.getUTF8Width(buffer);
        u8g2.printf(girdWidth * x + girdWidth / 2 - width / 2, y * girdHeight + girdHeight / 2 + 2, buffer);
    }
}


// 方向
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define SIZE 4

// 移动数组
/**
 *  2048的逻辑
 *  chatgpt生成的,很好用
 * @param mat
 * @param direction
 */
void move(uint16_t mat[SIZE][SIZE], int direction) {
    int i, j, current, last_merge;

    switch (direction) {
        case UP:
            for (j = 0; j < SIZE; j++) {
                current = 0;
                last_merge = -1;
                for (i = 0; i < SIZE; i++) {
                    if (mat[i][j] != 0) {
                        if (current != i) {
                            mat[current][j] = mat[i][j];
                            mat[i][j] = 0;
                        }
                        if (last_merge != -1 && mat[current][j] == mat[last_merge][j]) {
                            mat[last_merge][j] *= 2;
                            mat[current][j] = 0;
                        } else {
                            last_merge = current;
                            current++;
                        }
                    }
                }
            }
            break;

        case RIGHT:
            for (i = 0; i < SIZE; i++) {
                current = SIZE - 1;
                last_merge = -1;
                for (j = SIZE - 1; j >= 0; j--) {
                    if (mat[i][j] != 0) {
                        if (current != j) {
                            mat[i][current] = mat[i][j];
                            mat[i][j] = 0;
                        }
                        if (last_merge != -1 && mat[i][current] == mat[i][last_merge]) {
                            mat[i][last_merge] *= 2;
                            mat[i][current] = 0;
                        } else {
                            last_merge = current;
                            current--;
                        }
                    }
                }
            }
            break;

        case DOWN:
            for (j = 0; j < SIZE; j++) {
                current = SIZE - 1;
                last_merge = -1;
                for (i = SIZE - 1; i >= 0; i--) {
                    if (mat[i][j] != 0) {
                        if (current != i) {
                            mat[current][j] = mat[i][j];
                            mat[i][j] = 0;
                        }
                        if (last_merge != -1 && mat[current][j] == mat[last_merge][j]) {
                            mat[last_merge][j] *= 2;
                            mat[current][j] = 0;
                        } else {
                            last_merge = current;
                            current--;
                        }
                    }
                }
            }
            break;

        case LEFT:
            for (i = 0; i < SIZE; i++) {
                current = 0;
                last_merge = -1;
                for (j = 0; j < SIZE; j++) {
                    if (mat[i][j] != 0) {
                        if (current != j) {
                            mat[i][current] = mat[i][j];
                            mat[i][j] = 0;
                        }
                        if (last_merge != -1 && mat[i][current] == mat[i][last_merge]) {
                            mat[i][last_merge] *= 2;
                            mat[i][current] = 0;
                        } else {
                            last_merge = current;
                            current++;
                        }
                    }
                }
            }
            break;
    }
}

void Game2048::run() {
    uint16_t mat[4][4] = {0};
    ((uint16_t *) mat)[getRandomNumber()%16]=2;


    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        u8g2.clearBuffer();

        drawGird();

        bool needNewNumber = false;
        if (keyCheck(KEY_B_UP)) {
            move(mat, UP);
            needNewNumber= true;
        }
        if (keyCheck(KEY_B_DOWN)) {
            move(mat, DOWN);
            needNewNumber= true;
        }
        if (keyCheck(KEY_B_LEFT)) {
            move(mat, LEFT);
            needNewNumber= true;
        }
        if (keyCheck(KEY_B_RIGHT)) {
            move(mat, RIGHT);
            needNewNumber= true;
        }

        if (needNewNumber){
            uint8_t freeIndex[16]={0};
            uint8_t count=0;
            for (int i = 0; i < 16; ++i) {
                if (((uint16_t *) mat)[i]==0){
                    freeIndex[count]=i;
                    count++;
                }
            }

            if (count!=0){
                uint32_t  index = getRandomNumber() % count;
                ((uint16_t *) mat)[freeIndex[index]]=2;
            }

        }


        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                draw(x, y, mat[y][x]);
            }
        }

        u8g2.sendBuffer();
    }


}
