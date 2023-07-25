import cv2
import numpy as np


def convert_to_chromakey_binary(input_video_path):
    pixel_data = []


    # 打开视频文件
    cap = cv2.VideoCapture(input_video_path)

    # 检查是否成功打开视频
    if not cap.isOpened():
        print("Error: 无法打开视频文件.")
        return

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        frame = cv2.resize(frame, (64, 64))

        # 将BGR图像转换为HSV图像
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 定义绿色范围
        lower_green = np.array([40, 40, 40])  # 绿幕的下界
        upper_green = np.array([80, 255, 255])  # 绿幕的上界

        # 创建一个掩膜，只保留绿色区域
        mask = cv2.inRange(hsv_frame, lower_green, upper_green)

        # 将掩膜应用于原始帧
        chromakey_binary_frame = cv2.bitwise_not(mask)

        pixel_data.append(chromakey_binary_frame.flatten() // 255)


    # 显示二值化图像（可选）
        cv2.imshow('Chromakey Binary', chromakey_binary_frame)
        if cv2.waitKey(1) & 0xFF == 27:  # 按ESC键退出
            break

    cap.release()
    cv2.destroyAllWindows()  # 如果您希望在执行结束后关闭显示窗口，取消注释这一行

         # 将像素数据转换为numpy数组
    pixel_data = np.concatenate(pixel_data)

    # 压缩像素数据，使每个像素只占用1个比特
    compressed_data = np.packbits(pixel_data)

    # 将压缩后的数据写入到bin文件
    with open(r"C:\Users\Legend\CLionProjects\quicklzzz\cmake-build-debug\in.bin", 'wb') as f:
        f.write(compressed_data.tobytes())

if __name__ == "__main__":
    input_video_path = "ikun_basketball.mp4"  # 替换为您的输入视频文件路径
    convert_to_chromakey_binary(input_video_path)
