#include "Gomoku.h"

#define    BOARD_SIZE    13

#include "./maxigo/board.h"

#include "resource/IMAGE_gomoku_black.h"
#include "resource/IMAGE_gomoku_white.h"
#include "app/common/Sprite.h"


//#define STONE_BLACK 1
//#define STONE_EMPTY 0
//#define STONE_WHITE -1
#define OFFSET_X 32
#define GIRD 5

void Gomoku::drawPiece(uint8_t x, uint8_t y, piece_t piece) {
    switch (piece) {
        case STONE_BLACK: {
            black->draw(OFFSET_X + x * GIRD, y * GIRD);
            break;
        }
        case STONE_WHITE: {
            white->draw(OFFSET_X + x * GIRD, y * GIRD);
            break;
        }
    }
}

void Gomoku::drawBox(uint8_t x, uint8_t y) {
    u8g2.drawFrame(OFFSET_X + x * GIRD - 1, y * GIRD - 1, 6, 6);
}

void Gomoku::run() {
    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();


    Sprite _black(IMAGE_gomoku_black_width, IMAGE_gomoku_black_height, IMAGE_gomoku_black);
    black = &_black;
    Sprite _white(IMAGE_gomoku_white_width, IMAGE_gomoku_white_height, IMAGE_gomoku_white);
    white = &_white;


    STONE_BLACK; //黑子先下
    Board board;


    bool blink = true;
    uint8_t blinkCount = 0;

    uint8_t cursorX = 0;
    uint8_t cursorY = 0;
    {
        move_t move = board.negamax(1, STONE_BLACK); //ai走第一步
        board.move(move.y, move.x, STONE_BLACK);
    }

    piece_t winner = STONE_EMPTY;


    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        u8g2.clearBuffer();

        //画所有棋子
        for (int y = 0; y < BOARD_SIZE; ++y) { //可以优化,但没必要,反正渲染挺快的
            for (int x = 0; x < BOARD_SIZE; ++x) {
                drawPiece(x, y, board.signMap[y][x]);
            }
        }

        if (winner != STONE_EMPTY) {
            if (winner == STONE_WHITE) {
                u8g2.printf(10, displayHeight / 2, "You Win!");
            } else {
                u8g2.printf(10, displayHeight / 2, "You lose!");
            }
            u8g2.sendBuffer();
            keyWaitAnyKey();
            return;
        }

        //应该不会下满棋盘吧....
        //if (下满棋盘){
        //    平局
        //}

        /**
         * 落子逻辑
         */
        {
            //待选下子位置闪烁
            if (blinkCount++ % 7 == 0) {
                blink = !blink;
            }

            //处理按键
            int8_t moveX = 0;
            int8_t moveY = 0;
            if (keyCheck(KEY_B_UP)) {
                moveX = 0;
                moveY = -1;
            }
            if (keyCheck(KEY_B_DOWN)) {
                moveX = 0;
                moveY = 1;
            }
            if (keyCheck(KEY_B_LEFT)) {
                moveY = 0;
                moveX = -1;
            }
            if (keyCheck(KEY_B_RIGHT)) {
                moveY = 0;
                moveX = 1;
            }
            if (cursorX + moveX < BOARD_SIZE and cursorX + moveX >= 0 and
                cursorY + moveY < BOARD_SIZE and cursorY + moveY >= 0) { //防止超过棋盘
                cursorX = cursorX + moveX;
                cursorY = cursorY + moveY;
                if (blink) {
                    int8_t piece = board.signMap[cursorY][cursorX];
                    if (piece == STONE_EMPTY) {
                        drawPiece(cursorX, cursorY, STONE_WHITE);
                    } else { //游标的位置有子时,绘制一个方框
                        drawBox(cursorX, cursorY);
                    }
                }
            }
            // 画游标
            if (keyCheck(KEY_B)) {
                int8_t piece = board.signMap[cursorY][cursorX];
                if (piece == STONE_EMPTY) {
                    board.move(cursorY, cursorX, STONE_WHITE);
                    if (board.winner_at(cursorY, cursorX)) {
                        winner = STONE_WHITE;
                    }
                    // ai走
                    {
                        move_t move = board.negamax(1, STONE_BLACK);
                        board.move(move.y, move.x, STONE_BLACK);
                        if (board.winner_at(move.y, move.x)) {
                            //黑色胜
                            winner = STONE_BLACK;
                        }

                    }
                }
            }
        }

        u8g2.sendBuffer();
    }


}
