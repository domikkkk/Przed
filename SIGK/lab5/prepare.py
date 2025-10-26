import cv2
import os

def resize_and_crop(image_path, output_path, new_size=256):
    img = cv2.imread(image_path)
    height, width = img.shape[:2]

    # Get smaller edge
    mini = min(height, width)
    scale = mini / new_size

    # Resize
    img_resized = cv2.resize(img, (int(width/scale), int(height/scale)))

    new_height, new_width = img_resized.shape[:2]

    x_start = (new_width - new_size) // 2
    y_start = (new_height - new_size) // 2

    img_cropped = img_resized[y_start:y_start+new_size,
                              x_start:x_start+new_size]

    cv2.imwrite(output_path, img_cropped)


def process_folder(input_folder, output_folder, new_size=256):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    for folder in os.listdir(input_folder):
        folder_path = os.path.join(input_folder, folder)
        output_subfolder = os.path.join(output_folder, folder)
        if not os.path.exists(output_subfolder):
            os.makedirs(output_subfolder)
        for filename in os.listdir(folder_path):
            input_path = os.path.join(folder_path, filename)
            output_path = os.path.join(output_subfolder, filename)
            resize_and_crop(input_path, output_path, new_size=new_size)


process_folder("./atd_12k/datasets/train_10k", "./atd_12k/datasets/train_128px", 128)
