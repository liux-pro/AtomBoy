#include "Gomoku.h"

#define    BOARD_SIZE    15

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


void Gomoku::run() {
    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();


    Sprite _black(IMAGE_gomoku_black_width, IMAGE_gomoku_black_height, IMAGE_gomoku_black);
    black = &_black;
    Sprite _white(IMAGE_gomoku_white_width, IMAGE_gomoku_white_height, IMAGE_gomoku_white);
    white = &_white;


    piece_t player = STONE_BLACK;
    Board board;
    int8_t count=0;



    while (true) {


        move_t move = board.negamax(1, player);
        board.move(move.y, move.x, player);
        u8g2.clearBuffer();
        for (int y = 0; y < BOARD_SIZE; ++y) { //可以优化,但没必要,反正渲染挺快的
            for (int x = 0; x < BOARD_SIZE; ++x) {
                drawPiece(x, y, board.signMap[y][x]);
            }
        }
        u8g2.sendBuffer();


        if (board.winner_at(move.y, move.x)) { //
            piece_t color = player;

            int8_t dx[4] = {0, 1, 1, 1}; // 四个方向
            int8_t dy[4] = {1, 0, 1, -1};

            for (int i = 0; i < 4; i++) {
                int8_t nx = move.x + dx[i];
                int8_t ny = move.y + dy[i];
                count = 1; // 已知一个(x, y)坐标在该条线上

                while (board.is_in( ny,nx) && board.signMap[ny][nx] == color) {
                    count++;
                    nx += dx[i];
                    ny += dy[i];
                }

                int8_t nx_ = move.x - dx[i];
                int8_t ny_ = move.y - dy[i];

                while (board.is_in( ny_,nx_) && board.signMap[ny_][nx_] == color) {
                    count++;
                    nx_ -= dx[i];
                    ny_ -= dy[i];
                }

                if (count >= 5) {
                    u8g2.drawLine((nx - dx[i])*GIRD + GIRD/2+32, (ny - dy[i])*GIRD + GIRD/2,
                                  (nx_ + dx[i])*GIRD + GIRD/2+32, (ny_ + dy[i])*GIRD + GIRD/2);
                    break;
                }
            }
            u8g2.sendBuffer();
            while (1);
        }
        player *= -1;
    }


}
