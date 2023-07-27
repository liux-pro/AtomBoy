#include "IKun.h"
#include "ikun_basketball_compressed.h"
#include "quicklz.h"
#include "IMAGE_ikun_basketball_ikun_basketball.h"

static void decompress(const uint8_t *in, const uint8_t *out) {
    qlz_state_decompress state_decompress;
    memset(&state_decompress, 0, sizeof(state_decompress));
    qlz_decompress(reinterpret_cast<const char *>(in), (void *) out, &state_decompress);
}

const uint16_t offset[] = {0, 200, 409, 621, 817, 988, 1125, 1236, 1344, 1474, 1622, 1775, 1936, 2113, 2294, 2473, 2654,
                           2843, 3033, 3234, 3445, 3661, 3869, 4046, 4191, 4332, 4451, 4584, 4731, 4883, 5031, 5191,
                           5345, 5515, 5678, 5859};

void IKun::run() {
    u8g2.setColorIndex(1);
    u8g2.setFontPosTop();

    constexpr size_t offsetSize = sizeof(offset) / sizeof(uint16_t);
    uint16_t offsetIndex = 0;
    int8_t offsetDirection = 1;


    while (true) {
        keyScan();
        u8g2.clearBuffer();
        uint8_t buf[1024];

        decompress(ikun_basketball_compressed + offset[offsetIndex], buf);

        if (offsetIndex == 0) {
            offsetDirection = 1;
        }
        if (offsetIndex == (offsetSize - 1)) {
            offsetDirection = -1;
        }
        offsetIndex = offsetIndex + offsetDirection;


        u8g2.drawXBM(0, 0, 64, 64, buf);
        u8g2.drawXBM(64, 0, 64, 64, buf);


        u8g2.sendBuffer();
    }
}
