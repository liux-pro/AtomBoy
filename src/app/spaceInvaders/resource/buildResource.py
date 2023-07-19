import cv2
import numpy as np
import requests

from src.app.image_util import image_list_to_header, img_grap

# 资源图片来自
# http://minecraftpixelartbuildingideas.blogspot.com/2015/06/minecraft-pixel-art-space-invaders.html


image = cv2.imread("space-invader.png", cv2.IMREAD_UNCHANGED)

# 如果图像具有透明通道
if image.shape[2] == 4:
    # 将透明像素的RGB值设置为白色
    image[np.where(image[:, :, 3] == 0)] = [255, 255, 255, 255]

# 将帧转换为灰度图像
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 进行二值化处理
_, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
binary = cv2.bitwise_not(binary)

alienA_list = []
grab = img_grap(binary, 0, 0, 8, 8)
alienA_list.append(grab)
# cv2.imwrite("1.png", grab)

grab = img_grap(binary, 0, 9, 8, 8)
alienA_list.append(grab)
# cv2.imwrite("2.png", grab)

image_list_to_header(alienA_list, "spaceInvaders", "alienA")

alienB_list = []
grab = img_grap(binary, 9, 0, 12, 8)
alienB_list.append(grab)
# cv2.imwrite("1.png", grab)

grab = img_grap(binary, 9, 9, 12, 8)
alienB_list.append(grab)
# cv2.imwrite("2.png", grab)

image_list_to_header(alienB_list, "spaceInvaders", "alienB")

alienC_list = []
grab = img_grap(binary, 22, 0, 11, 8)
alienC_list.append(grab)
# cv2.imwrite("1.png", grab)

grab = img_grap(binary, 22, 9, 11, 8)
alienC_list.append(grab)
# cv2.imwrite("2.png", grab)

image_list_to_header(alienC_list, "spaceInvaders", "alienC")


grab = img_grap(binary, 0, 18, 15, 8)
image_list_to_header([grab], "spaceInvaders", "user")

grab = img_grap(binary, 17, 19, 16, 7)
image_list_to_header([grab], "spaceInvaders", "UFO")
