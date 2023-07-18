import cv2
import os


# 把图片转成c语言数组,xbm格式

def image_list_to_header(image_list: list, app, name):
    if len(image_list) < 1:
        print("at least 1 image")
        return
    height, width = image_list[0].shape
        # 转换为u8g2.drawXBM格式的数据
    xbm_data = []
    for binary_image in image_list:
        for y in range(0, height):
            line = "\t"
            for x in range(0, width, 8):
                byte = 0
                for bit in range(8):
                    if x + bit < width and binary_image[y, x + bit] > 0:
                        byte |= (1 << bit)
                line += "0x{:02X}, ".format(byte)
            xbm_data.append(line)

    # 打开头文件
    header_file = open(f"IMAGE_{app}_{name}.h", 'w')

    # 写入数据到头文件
    header_file.write("#pragma once\n")
    header_file.write("\n")
    header_file.write(f"#define IMAGE_{app}_{name}_width {width}\n")
    header_file.write(f"#define IMAGE_{app}_{name}_height {height}\n")
    header_file.write(f"#define IMAGE_{app}_{name}_maxStep {len(image_list)}\n")
    header_file.write("\n")
    header_file.write(f"const unsigned char IMAGE_{app}_{name}[] = {{\n")

    for line in xbm_data:
        header_file.write(line + "\n")

    header_file.write("};\n")

    # 关闭头文件
    header_file.close()


def img_grap(img, x, y, w, h):
    # 裁剪图像
    cropped_image = img[y:y + h, x:x + w]
    return cropped_image
