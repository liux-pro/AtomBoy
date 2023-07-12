import cv2
import os


# 把图片转成c语言数组,xbm格式

def img_to_header(image_file, app):
    # 读取图像文件
    image = cv2.imread(image_file, cv2.IMREAD_GRAYSCALE)

    # 将图像转换为二值图像（黑白）
    _, binary_image = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY)

    # 获取图像尺寸
    height, width = binary_image.shape

    # 转换为u8g2.drawXBM格式的数据
    xbm_data = []
    for y in range(0, height):
        line = "\t"
        for x in range(0, width, 8):
            byte = 0
            for bit in range(8):
                if x + bit < width and binary_image[y, x + bit] > 0:
                    byte |= (1 << bit)
            line += "0x{:02X}, ".format(byte)
        xbm_data.append(line)

    name = os.path.basename(image_file).split(".")[0]
    # 打开头文件
    header_file = open("IMAGE_" + name + ".h", 'w')

    # 写入数据到头文件
    header_file.write("#pragma once\n")
    header_file.write("\n")
    header_file.write(f"#define IMAGE_{app}_{name}_width {width}\n")
    header_file.write(f"#define IMAGE_{app}_{name}_height {height}\n")
    header_file.write("\n")
    header_file.write(f"const unsigned char IMAGE_{app}_{name}[] = {{\n")

    for line in xbm_data:
        header_file.write(line + "\n")

    header_file.write("};\n")

    # 关闭头文件
    header_file.close()

