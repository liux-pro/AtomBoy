#pragma once

#include "Arduino.h"
#include "U8g2lib.h"

#define CALCULATE_XBM_IMAGE_SIZE(width, height) (((width) + 7) / 8 * (height))

class Sprite {
protected:
    const uint8_t width;
    const uint8_t height;
    const uint8_t* image;
    const uint32_t imageSize{};
    uint8_t step{};
    uint8_t maxStep=1;
    uint8_t speed=0;

public:
    /**
     * 序列帧动画,但是只有一帧,实际只是个图片,不会动
     * @param width 宽度
     * @param height 高度
     * @param image 图像指针
     */
    Sprite(uint8_t width, uint8_t height, const uint8_t* image);
    /**
     * 序列帧动画
     * @param width 宽度
     * @param height 高度
     * @param image 图像指针
     * @param maxStep 动画一共有几帧
     * @param speed 每经过几帧播放一帧动画,例如设置位10,屏幕刷新率为60,则每秒播放6帧
     */
    Sprite(uint8_t width, uint8_t height, const uint8_t* image, uint8_t maxStep,uint8_t speed);
    void draw(uint8_t x, uint8_t y);
};
