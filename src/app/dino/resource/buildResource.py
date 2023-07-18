import cv2
import numpy as np
import requests

from src.app.image_util import image_list_to_header, img_grap

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

# 小恐龙动画,三帧
dino_list = []
grab = img_grap(binary, 850 + 44 * 0, 4, 40, 43)
resize = cv2.resize(grab, (20, 20), interpolation=cv2.INTER_NEAREST)
dino_list.append(resize)

grab = img_grap(binary, 850 + 44 * 2, 4, 40, 43)
resize = cv2.resize(grab, (20, 20), interpolation=cv2.INTER_NEAREST)
dino_list.append(resize)

grab = img_grap(binary, 850 + 44 * 3, 4, 40, 43)
resize = cv2.resize(grab, (20, 20), interpolation=cv2.INTER_NEAREST)
dino_list.append(resize)

image_list_to_header(dino_list, "dino", "dino")

# 鸟的动画
bird_list = []
grab = img_grap(binary, 136 + 46 * 0, 4, 42, 36)
resize = cv2.resize(grab, (21, 18), interpolation=cv2.INTER_NEAREST)
bird_list.append(resize)

grab = img_grap(binary, 136 + 46 * 1, 4, 42, 36)
resize = cv2.resize(grab, (21, 18), interpolation=cv2.INTER_NEAREST)
bird_list.append(resize)

image_list_to_header(bird_list, "dino", "bird")

# 树

grab = img_grap(binary, 229, 3, 15, 33)
resize = cv2.resize(grab, (8, 16), interpolation=cv2.INTER_NEAREST)
image_list_to_header([resize], "dino", "treeA")

grab = img_grap(binary, 383, 3, 23, 46)
resize = cv2.resize(grab, (13, 28), interpolation=cv2.INTER_NEAREST)
image_list_to_header([resize], "dino", "treeB")
