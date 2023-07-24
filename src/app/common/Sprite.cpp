#include "Sprite.h"
#include "fps/fps.h"


Sprite::Sprite(uint8_t width, uint8_t height, const uint8_t *image)
        : width(width), height(height), image(image),
          imageSize(CALCULATE_XBM_IMAGE_SIZE(width, height)) {}

Sprite::Sprite(uint8_t width, uint8_t height, const uint8_t *image, uint8_t maxStep, uint8_t speed)
        : width(width), height(height), image(image),
          imageSize(CALCULATE_XBM_IMAGE_SIZE(width, height)),
          maxStep(maxStep), speed(speed) {}

void Sprite::draw(uint8_t x, uint8_t y) {
    if (speed == 0) {
        u8g2.drawXBM(x, y, width, height, image);
        return;
    }
    u8g2.drawXBM(x, y, width, height, image + ((fps_get_frame() / speed % maxStep) * imageSize));
}
