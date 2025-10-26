import numpy as np
import cv2
import os
from torch.utils.data import Dataset
import torch
from torchvision.transforms import ToTensor, Compose, Lambda, Normalize

os.environ['OPENCV_IO_ENABLE_OPENEXR'] = "1"


transform = Compose([
    ToTensor(),  # -> magicznie zmienia 32x32x3 -> 3x32x32, ale to dobrze bo tego oczekujemy
])


def read_exr(im_path: str) -> np.ndarray:
    return cv2.imread(
        filename=im_path,
        flags=cv2.IMREAD_ANYCOLOR | cv2.IMREAD_ANYDEPTH
    )


def normalize(img):
    return img * (0.5 / np.mean(img))


class EXRDataset(Dataset):
    def __init__(self, images_folder, transform=transform):
        self.folder = images_folder
        self.images = self.read_images()
        self.transform = transform

    def read_images(self):
        images = []
        for filename in os.listdir(self.folder):
            image_name = os.path.join(self.folder, filename)
            img = read_exr(image_name)
            images.append(img)
        return images

    def __len__(self):
        return len(self.images)

    def __getitem__(self, index):
        image = normalize(self.images[index])
        if self.transform:
            image = self.transform(image)
        return image
