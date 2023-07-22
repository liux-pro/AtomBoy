#include "Menu.h"
#include "app/common/AtomUI.h"
#include "fps/fps.h"
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))


//主菜单内容
const char *menu_main1[] = {
        "- 1 Dino",
        "- 2 FlappyBird",
        "- 3",
        "- 4 你好",
        "- 5 ",
        "- 6",
        "- 7 cccccccc",
        "- 8",
        "- 9",
        "- 10 end",
};

void Menu::run() {
    AtomUI::List list(const_cast<char **>(menu_main1), ARRAY_LENGTH(menu_main1));
    AtomUI::Cursor cursor(&list);

    while (true) {
        if (!fps_need_refresh()) {
            continue;
        }
        keyScan();
        if (keyCheck(KEY_B)) {
            nextApplication = cursor.getSelectedIndex()+1;
            return;
        }

        if (keyCheck(KEY_B_DOWN)) {
            cursor.down();
        }

        if (keyCheck(KEY_B_UP)) {
            cursor.up();
        }

        u8g2.clearBuffer();
        list.draw();
        cursor.draw();
        u8g2.sendBuffer();
    }

}