#include "AtomUI.h"
#include "Arduino.h"

extern U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI u8g2;


namespace AtomUI {
    Animation::Animation() {
        slotSizeScreen = u8g2.getHeight() / HEIGHT;
    }

    uint8_t Animation::getPosition() const {
        return position;
    }

    void Animation::calculateY() {
        auto targetY = position * HEIGHT;
        if (speed == 0) {
            currentY = targetY;
        } else {
            currentY = currentY + speed;
            if (speed > 0) {
                if (currentY >= targetY) {
                    currentY = targetY;
                    speed = 0;
                }
            } else if (speed < 0) {
                if (currentY <= targetY) {
                    currentY = targetY;
                    speed = 0;
                }
            }
        }
    }

    void Animation::up() {
        if (position > 0) {
            position--;
            speed = -SPEED;
        }
    }

    List::List(char *list[], int size) {
        this->listSize = size;
        this->list = list;

        if (listSize > slotSizeScreen) {
            allowScroll = true;
        }
    }

    uint8_t List::getSize() {
        return listSize;
    }

    void List::draw() {
        if (allowScroll) {
            calculateY();
        }

        for (int i = 0; i < listSize; ++i) {
            u8g2.setDrawColor(1);
            u8g2.drawUTF8(OFFSET_X, i * HEIGHT + OFFSET_Y - currentY, list[i]);
        }
    }

    uint8_t List::getWidth(int screenY) {
        screenY = screenY + currentY;

        int index = screenY / HEIGHT;

        int remainder = screenY % HEIGHT;
        if (remainder == 0) {
            return u8g2.getUTF8Width(list[index]);
        } else {
            auto fixedPoint = 1024;
            int percent = remainder * fixedPoint / HEIGHT;
            auto fromWidth = u8g2.getUTF8Width(list[index]);
            auto toWidth = u8g2.getUTF8Width(list[index + 1]);
            auto width = fromWidth + (toWidth - fromWidth) * percent / fixedPoint;
            return width;
        }
    }

    void List::down() {
        if (allowScroll) {
            if (position < listSize - slotSizeScreen) {
                position++;
                speed = SPEED;
            }
        }
    }

    Cursor::Cursor(Item *item) {
        this->item = item;
        slotSize = MIN(this->item->getSize(), slotSizeScreen);
    }

    void Cursor::up() {
        if (position > 0) {
            position--;
            speed = -SPEED;
        } else {
            item->up();
        }
    }

    void Cursor::down() {
        if (position < slotSize - 1) {
            position++;
            speed = SPEED;
        } else {
            item->down();
        }
    }

    void Cursor::draw() {
        u8g2.setDrawColor(2);
        calculateY();
        u8g2.drawRBox(OFFSET_X, currentY + OFFSET_Y,
                      item->getWidth(currentY) + OFFSET_WIDTH,
                      OFFSET_HEIGHT,
                      RADIUS);
    }

    uint8_t Cursor::getSelectedIndex() {
        return item->getPosition() + position;
    }
}
