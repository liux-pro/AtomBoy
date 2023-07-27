#include "Menu.h"
#include "app/common/AtomUI.h"
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))


//主菜单内容
const char *menu_main1[] = {
        "- Dino",
        "- Flappy Bird",
        "- Snake",
        "- Gomoku",
        "- 2048",
        "- Space Invaders",
        "- IKUN",
};

void Menu::run() {
    AtomUI::List list(const_cast<char **>(menu_main1), ARRAY_LENGTH(menu_main1));
    AtomUI::Cursor cursor(&list);

    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        if (keyCheck(KEY_AB)) {
            nextApplication = cursor.getSelectedIndex()+1;
            return;
        }

        if (keyCheck(KEY_AB_DOWN)) {
            cursor.down();
        }

        if (keyCheck(KEY_AB_UP)) {
            cursor.up();
        }

        u8g2.clearBuffer();
        list.draw();
        cursor.draw();
        u8g2.sendBuffer();
    }

}