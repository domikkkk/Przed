from __future__ import print_function, division
from loguru import logger as loguru_logger
import sys
import os
import numpy as np
import torch
from PIL import Image

sys.path.append(os.path.join(os.path.dirname(__file__), 'MemFlow'))
sys.path.append('core')

from MemFlow.core.Networks import build_network
from MemFlow.core.utils import flow_viz
from MemFlow.core.utils import frame_utils
from MemFlow.core.utils.utils import InputPadder, forward_interpolate
from MemFlow.inference import inference_core_skflow as inference_core
from MemFlow.configs.sintel_memflownet import get_cfg



def count_parameters(model):
    return sum(p.numel() for p in model.parameters() if p.requires_grad)


@torch.no_grad()
def inference(cfg, image1, image2, save=False, verbose=False):
    model = build_network(cfg).cuda()
    if verbose:
        loguru_logger.info("Parameter Count: %d" % count_parameters(model))

    if cfg.restore_ckpt is not None:
        if verbose:
            print("[Loading ckpt from {}]".format(cfg.restore_ckpt))
        ckpt = torch.load(cfg.restore_ckpt, map_location='cpu')
        ckpt_model = ckpt['model'] if 'model' in ckpt else ckpt
        if 'module' in list(ckpt_model.keys())[0]:
            for key in ckpt_model.keys():
                ckpt_model[key.replace('module.', '', 1)] = ckpt_model.pop(key)
            model.load_state_dict(ckpt_model, strict=True)
        else:
            model.load_state_dict(ckpt_model, strict=True)

    model.eval()

    if verbose:
        print(f"preparing images...")
    img1 = torch.from_numpy(image1).permute(2, 0, 1).float()
    img2 = torch.from_numpy(image2).permute(2, 0, 1).float()

    images = torch.stack([img1, img2])  # T=2

    processor = inference_core.InferenceCore(model, config=cfg)
    images = images.cuda().unsqueeze(0)  # 1, T, C, H, W

    padder = InputPadder(images.shape)
    images = padder.pad(images)

    images = 2 * (images / 255.0) - 1.0
    flow_prev = None
    results = []
    if verbose:
        print(f"start inference...")

    for ti in range(images.shape[1] - 1):
        flow_low, flow_pre = processor.step(images[:, ti:ti + 2], end=(ti == images.shape[1] - 2),
                                            add_pe=('rope' in cfg and cfg.rope), flow_init=flow_prev)
        flow_pre = padder.unpad(flow_pre[0]).cpu()
        results.append(flow_pre)
        if 'warm_start' in cfg and cfg.warm_start:
            flow_prev = forward_interpolate(flow_low[0])[None].cuda()

    if not os.path.exists(cfg.vis_dir):
        os.makedirs(cfg.vis_dir)

    flow_img = flow_viz.flow_to_image(results[0].permute(1, 2, 0).numpy())
    if save:
        image = Image.fromarray(flow_img)
        image.save('{}/flow_{:04}_to_{:04}.png'.format(cfg.vis_dir, 1, 2))

    return flow_img


def generates_flow(img1, img2, save=False, verbose=False):
    img1 = img1.permute(1, 2, 0).numpy()
    img2 = img2.permute(1, 2, 0).numpy()
    img1 = (img1 + 1) / 2
    img1 = (img1 * 255).astype(np.uint8)

    img2 = (img2 + 1) / 2
    img2 = (img2 * 255).astype(np.uint8)

    cfg = get_cfg()

    cfg.name = "MemFlowNet"
    cfg.restore_ckpt = "MemFlow/ckpts/MemFlowNet_sintel.pth"
    cfg.vis_dir = "./"

    return inference(cfg, img1, img2, save, verbose)
