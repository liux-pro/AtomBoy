import cv2
import numpy as np
import requests

from src.app.image_util import img_to_header

# 这个资源文件是chromium源代码里扒出来的
dino_img_url = r"https://cdn.jsdelivr.net/gh/chromium/chromium@117.0.5881.2/components/neterror/resources/images/default_100_percent/offline/100-offline-sprite.png"
result = requests.get(dino_img_url)
with open("dino.png", "wb") as fo:
    fo.write(result.content)

image = cv2.imread("dino.png", cv2.IMREAD_UNCHANGED)
# 如果图像具有透明通道
if image.shape[2] == 4:
    # 将透明像素的RGB值设置为白色
    image[np.where(image[:, :, 3] == 0)] = [255, 255, 255, 255]

# 将帧转换为灰度图像
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 进行二值化处理
_, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
binary = cv2.bitwise_not(binary)


def img_grap(img, x, y, w, h):
    # 裁剪图像
    cropped_image = img[y:y + h, x:x + w]
    return cropped_image


for i in range(5):
    grab = img_grap(binary, 850 + 44 * i, 4, 40, 43)
    resize = cv2.resize(grab, (20, 20), interpolation=cv2.INTER_NEAREST)
    cv2.imwrite(f"dino{i}.bmp", resize)
    img_to_header(f"dino{i}.bmp", "dino")

for i in range(2):
    grab = img_grap(binary, 136 + 46 * i, 4, 42, 36)
    resize = cv2.resize(grab, (21, 18), interpolation=cv2.INTER_NEAREST)
    cv2.imwrite(f"bird{i}.bmp", resize)
    img_to_header(f"bird{i}.bmp", "dino")

grab = img_grap(binary, 229, 3, 15, 33)
resize = cv2.resize(grab, (8, 16), interpolation=cv2.INTER_NEAREST)
cv2.imwrite(f"tree0.bmp", resize)
img_to_header(f"tree0.bmp", "dino")

grab = img_grap(binary, 383, 3, 23, 46)
resize = cv2.resize(grab, (13, 28), interpolation=cv2.INTER_NEAREST)
cv2.imwrite(f"tree1.bmp", resize)
img_to_header(f"tree1.bmp", "dino")

# 将二值化图像转换为每个像素只占用1个比特的形式，并将其添加到列表中

# cv2.imshow("binary",binary)
cv2.waitKey(0)
