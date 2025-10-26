import lpips
import torch
import numpy as np
from math import log10
import matplotlib.pyplot as plt

loss_fn_alex = lpips.LPIPS(net='alex')


def SNE(img1: np.ndarray, img2: np.ndarray):
    img1_flatten, img2_flatten = img1.flatten(), img2.flatten()
    result = 0
    for pix1, pix2 in zip(img1_flatten, img2_flatten):
        result += pow(pix1-pix2, 2)
    return result


def PSNR(img1: np.ndarray, img2: np.ndarray, MAX=1):
    MSE = SNE(img1, img2) / img1.size
    return 10 * log10(pow(MAX, 2)/MSE)


def SSIM(img1: np.ndarray, img2: np.ndarray, L=255, k1=0.01, k2=0.03):

    mean1 = np.mean(img1)
    mean2 = np.mean(img2)
    var1 = np.var(img1)
    var2 = np.var(img2)
    cov = np.cov(img1.flatten(), img2.flatten())[0, 1]
    c1 = (k1 * L) ** 2
    c2 = (k2 * L) ** 2
    return (2 * mean1 * mean2 + c1) * (2 * cov + c2) / ((pow(mean1, 2) * pow(mean2, 2) + c1) * (var1 * var2 + c2))


def LPIPS(img1: np.ndarray, img2: np.ndarray):
    img1 = torch.from_numpy(img1).permute(2, 0, 1).unsqueeze(0).float()
    img2 = torch.from_numpy(img2).permute(2, 0, 1).unsqueeze(0).float()

    return loss_fn_alex(img1, img2).detach().item()


def get_all_metrics(img1: np.ndarray, img2: np.ndarray):
    return SNE(img1, img2), PSNR(img1, img2), SSIM(img1, img2), LPIPS(img1, img2)


def plot_metrics(imgs_groundtruth: list[np.ndarray], imgs_cv2: list[np.ndarray], imgs_model: list[np.ndarray]):
    sne_cv2_list, psnr_cv2_list, ssim_cv2_list, lpips_cv2_list = [], [], [], []
    sne_model_list, psnr_model_list, ssim_model_list, lpips_model_list = [], [], [], []

    for i, (img_groundtruth, img_cv2, img_model) in enumerate(zip(imgs_groundtruth, imgs_cv2, imgs_model)):
        sne_cv2, psnr_cv2, ssim_cv2, lpips_cv2 = get_all_metrics(img_groundtruth, img_cv2)
        sne_model, psnr_model, ssim_model, lpips_model = get_all_metrics(img_groundtruth, img_model)

        sne_cv2_list.append(sne_cv2)
        psnr_cv2_list.append(psnr_cv2)
        ssim_cv2_list.append(ssim_cv2)
        lpips_cv2_list.append(lpips_cv2)

        sne_model_list.append(sne_model)
        psnr_model_list.append(psnr_model)
        ssim_model_list.append(ssim_model)
        lpips_model_list.append(lpips_model)

    mean_sne_cv2, mean_psnr_cv2, mean_ssim_cv2, mean_lpips_cv2 = np.mean(sne_cv2_list), np.mean(psnr_cv2_list), np.mean(ssim_cv2_list), np.mean(lpips_cv2_list)
    mean_sne_model, mean_psnr_model, mean_ssim_model, mean_lpips_model = np.mean(sne_model_list), np.mean(psnr_model_list), np.mean(ssim_model_list), np.mean(lpips_model_list)

    fig, axs = plt.subplots(4, 1, figsize=(20, 20))

    # SNE
    axs[0].plot(sne_cv2_list, label="cv2", linestyle=' ', marker="o")
    axs[0].plot(sne_model_list, label="model", linestyle=' ', marker="s")
    axs[0].set_title("SNE")
    axs[0].set_xlabel("Image number")
    axs[0].set_ylabel("SNE")
    axs[0].legend()
    axs[0].grid(True)

    # PSNR
    axs[1].plot(psnr_cv2_list, label="cv2", linestyle=' ', marker="o")
    axs[1].plot(psnr_model_list, label="model", linestyle=' ', marker="s")
    axs[1].set_title("PSNR")
    axs[1].set_xlabel("Image number")
    axs[1].set_ylabel("PSNR")
    axs[1].legend()
    axs[1].grid(True)

    # SSIM
    axs[2].plot(ssim_cv2_list, label="cv2", linestyle=' ', marker="o")
    axs[2].plot(ssim_model_list, label="model", linestyle=' ', marker="s")
    axs[2].set_title("SSIM")
    axs[2].set_xlabel("Image number")
    axs[2].set_ylabel("SSIM")
    axs[2].legend()
    axs[2].grid(True)

    # LPIPS
    axs[3].plot(lpips_cv2_list, label="cv2", linestyle=' ', marker="o")
    axs[3].plot(lpips_model_list, label="model", linestyle=' ', marker="s")
    axs[3].set_title("LPIPS")
    axs[3].set_xlabel("Image number")
    axs[3].set_ylabel("LPIPS")
    axs[3].legend()
    axs[3].grid(True)

    plt.tight_layout()
    plt.show()

    print(f"""Metrics:
--------------------------------------------------
| Metric  | cv2        | Model      | Which Better
--------------------------------------------------
| SNE     | {mean_sne_cv2:10.4f} | {mean_sne_model:10.4f} | {"model" if mean_sne_cv2 > mean_sne_model else "cv2"}
| PSNR    | {mean_psnr_cv2:10.4f} | {mean_psnr_model:10.4f} | {"model" if mean_psnr_cv2 < mean_psnr_model else "cv2"}
| SSIM    | {mean_ssim_cv2:10.4f} | {mean_ssim_model:10.4f} | {"model" if mean_ssim_cv2 < mean_ssim_model else "cv2"}
| LPIPS   | {mean_lpips_cv2:10.4f} | {mean_lpips_model:10.4f} | {"model" if mean_lpips_cv2 > mean_lpips_model else "cv2"}
--------------------------------------------------""")
