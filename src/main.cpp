#include "Arduino.h"
#include "fps/fps.h"
#include "app/common/Application.h"
#include "app/menu/Menu.h"
#include "app/dino/Dino.h"
#include "app/flappyBird/FlappyBird.h"
#include "app/snake/Snake.h"
#include "app/gomoku/Gomoku.h"


U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI u8g2;


void setup() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_wqy12_t_chinese1);
    u8g2.setFontPosBaseline();
    fps_init();
}


void loop() {
    switch (nextApplication) {
        case APPLICATION_MENU : {
            Menu menu;
            menu.run();
            break;
        }
        case APPLICATION_DINO : {
            Dino dino;
            dino.run();
            break;
        }
        case APPLICATION_FLAPPY_BIRD : {
            FlappyBird flappyBird;
            flappyBird.run();
            break;
        }
        case APPLICATION_SNAKE : {
            Snake snake;
            snake.run();
            break;
        }
        case APPLICATION_GOMOKU : {
            Gomoku gomoku;
            gomoku.run();
            break;
        }
        default: {
            nextApplication = APPLICATION_DEFAULT;
        }
    }
}
