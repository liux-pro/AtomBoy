import cv2
import numpy as np
import requests

from src.app.image_util import image_list_to_header, img_grap

# 资源图片来自 https://gitlab.com/nowozin/maxigoarduboy


image = cv2.imread("white44.png", cv2.IMREAD_UNCHANGED)

# 如果图像具有透明通道
if image.shape[2] == 4:
    # 将透明像素的RGB值设置为白色
    image[np.where(image[:, :, 3] == 0)] = [255, 255, 255, 255]

# 将帧转换为灰度图像
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 进行二值化处理
_, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
# binary = cv2.bitwise_not(binary)

image_list_to_header([binary], "gomoku", "white")




image = cv2.imread("white44.png", cv2.IMREAD_UNCHANGED)

# 如果图像具有透明通道
if image.shape[2] == 4:
    # 将透明像素的RGB值设置为白色
    image[np.where(image[:, :, 3] == 0)] = [255, 255, 255, 255]

# 将帧转换为灰度图像
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 进行二值化处理
_, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
binary = cv2.bitwise_not(binary)

image_list_to_header([binary], "gomoku", "black")


