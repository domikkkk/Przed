import os.path

import moderngl
import numpy as np
from random import randint
from PIL import Image
from pyrr import Matrix44, Vector4

from base_window import BaseWindow


class PhongWindow(BaseWindow):

    def __init__(self, **kwargs):
        super(PhongWindow, self).__init__(**kwargs)
        self.frame = 0

    def init_shaders_variables(self):
        self.model_view_projection = self.program["model_view_projection"]
        self.model_matrix = self.program["model_matrix"]
        self.material_diffuse = self.program["material_diffuse"]
        self.material_shininess = self.program["material_shininess"]
        self.light_position = self.program["light_position"]
        self.camera_position = self.program["camera_position"]

    def is_visible(self, translation, view_matrix, proj_matrix):
        model_matrix = Matrix44.from_translation(translation)
        mvp = proj_matrix * view_matrix * model_matrix
        pos_clip = mvp * Vector4([0.0, 0.0, 0.0, 1.0])
        pos_clip = np.array(pos_clip)
        if pos_clip[3] == 0.0:
            return False
        ndc = pos_clip[:3] / pos_clip[3]
        return all(abs(coord) <= 1.0 for coord in ndc)

    def on_render(self, time: float, frame_time: float):
        self.ctx.clear(0.0, 0.0, 0.0, 0.0)
        self.ctx.enable(moderngl.DEPTH_TEST | moderngl.CULL_FACE)

        # todo: Randomize
        model_translation = np.random.randint(-20, 20, 3)
        
        # [15.0, 5.0, 0.0]

        camera_position = [5.0, 5.0, 15.0]
        model_matrix = Matrix44.from_translation(model_translation)
        proj = Matrix44.perspective_projection(45.0, self.aspect_ratio, 0.1, 1000.0)
        lookat = Matrix44.look_at(
            camera_position,
            (0.0, 0.0, 0.0),
            (0.0, 1.0, 0.0),
        )
        
        if not self.is_visible(model_translation, lookat, proj):
            return
        
        # [5.0, 0.0, 0.0]
        material_diffuse = np.random.randint(0, 255, 3) / 255.0
        # [1.0, 0.0, 0.0]
        material_shininess = randint(3, 20)
        # 5
        light_position = np.random.randint(-20, 20, 3)

        model_view_projection = proj * lookat * model_matrix

        self.model_view_projection.write(model_view_projection.astype('f4').tobytes())
        self.model_matrix.write(model_matrix.astype('f4').tobytes())
        self.material_diffuse.write(np.array(material_diffuse, dtype='f4').tobytes())
        self.material_shininess.write(np.array([material_shininess], dtype='f4').tobytes())
        self.light_position.write(np.array(light_position, dtype='f4').tobytes())
        self.camera_position.write(np.array(camera_position, dtype='f4').tobytes())

        self.vao.render()
        if self.output_path:
            img = (
                Image.frombuffer('RGBA', self.wnd.size, self.wnd.fbo.read(components=4))
                     .transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            )
            img.save(os.path.join(self.output_path, f'image_{self.frame:04}.png'))
            if self.frame == 0:
                with open("data.csv", "w") as fh:
                    fh.write("frame,model_translation,material_diffuse,material_shininess,light_position\n")
            with open("data.csv", "a") as fh:
                fh.write(f"{self.frame},\"{model_translation.tolist()}\",\"{material_diffuse.tolist()}\",{material_shininess},\"{light_position.tolist()}\"\n")
            self.frame += 1
