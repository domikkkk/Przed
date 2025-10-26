import numpy as np
import cv2
import os
from torch.utils.data import Dataset
from torchvision.transforms import ToTensor, Compose, Lambda, Normalize

transform = Compose([
    Lambda(lambda x: np.array(x, dtype=np.float32) / 255.0),
    ToTensor(),  # -> magicznie zmienia 32x32x3 -> 3x32x32, ale to dobrze bo tego oczekujemy
])


class ImageSet(Dataset):
    def __init__(self, images_folder, dest_folder, transform=None, impainting=False):
        self.folder = images_folder  # folder do obrazów  do przekształcenia (inputy)
        self.dest = dest_folder  # folder z docelowymi obrazami (outputy)
        self.images, self.dest_images = self.read_images(impainting)
        
        self.transform = transform

    def read_images(self, impainting=False):
        images = []
        dest_images = []
        for filename in os.listdir(self.dest):
            dest_img = cv2.imread(os.path.join(self.dest, filename))
            if impainting:
                read_folder = os.path.join(self.folder, filename.split(os.extsep)[0])
                for file in os.listdir(read_folder):
                    image_name = os.path.join(read_folder, file)
                    img = cv2.imread(image_name)
                    images.append(img)
                    dest_images.append(dest_img)
            else:
                image_name = os.path.join(self.folder, filename)
                img = cv2.imread(image_name)
                images.append(img)
                dest_images.append(dest_img)
        return images, dest_images

    def __len__(self):
        return len(self.images)

    def __getitem__(self, index):
        x_image = self.images[index]
        y_image = self.dest_images[index]
        if self.transform:
            x_image = self.transform(x_image)
            y_image = self.transform(y_image)
        return x_image, y_image
