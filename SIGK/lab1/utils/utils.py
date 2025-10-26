import cv2


def fix_colors(img):
    return cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
