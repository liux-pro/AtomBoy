#ifndef ANIMATION_H
#define ANIMATION_H

#include <cstdint>

namespace AtomUI {
    class Animation {
    protected:
        static constexpr int HEIGHT = 16;
        static constexpr int SPEED = 1;
        uint8_t position = 0;
        int8_t speed = 0;
        uint8_t slotSizeScreen = 0;
        int currentY = 0;

    public:
        Animation();

        [[nodiscard]] uint8_t getPosition() const;

        virtual void calculateY();

        virtual void up();

        virtual void down() = 0;

        virtual void draw() = 0;
    };

    class Item : public Animation {
    public:
        virtual uint8_t getWidth(int y) = 0;

        virtual uint8_t getSize() = 0;
    };

    class List : public Item {
    public:
        static constexpr int OFFSET_X = 0;
        static constexpr int OFFSET_Y = 13;
        bool allowScroll = false;
        uint8_t listSize;
        char **list;

    public:
        List(char *list[], int size);

        uint8_t getSize() override;

        void draw() override;

        uint8_t getWidth(int screenY) override;

        void down() override;
    };

    class Cursor : public Animation {
    private:
        static constexpr int RADIUS = 1;
        static constexpr int OFFSET_X = 0;
        static constexpr int OFFSET_Y = 1;
        static constexpr int OFFSET_WIDTH = 5;
        static constexpr int OFFSET_HEIGHT = 14;
        int slotSize = 0;
        Item *item;

    public:
        explicit Cursor(Item *item);

        void up() override;

        void down() override;

        void draw() override;

        uint8_t getSelectedIndex();
    };
}

#endif  // ANIMATION_H
