# LAB 1

## Pobieranie danych:
```sh
# Download High Resolution Images from: https://data.vision.ee.ethz.ch/cvl/DIV2K/ 
# and place them in /data/raw/test and /data/raw/valid or execute script below
sudo chmod +x download.sh
./download.sh

# Download required dependencies
pip install -r requirements.txt

# Prepare data for scalling and inpainting tasks
python preparing_data.py
```

## Zadanie 1 Scaling

Wejście to obrazy w rozdzielczości 32 x 32, zaś wyjście to obrazy w rozdzielczości 256 x 256.
Dane zostały przygotowane przez interpolacją dwuliniową: cv2.INTER_LINEAR.

Wyniki znajdują się w pliku [scaling.ipynb](scaling.ipynb).


## Zadanie 4 Inpainting

Wejście to obrazy w rozdzielczości 256 x 256 z losowo wyciętymi miejscami 32 x 32 lub też 3 x 3. Wyjście modelu to obraz w rozdzielczości 256 x 256 z uzupełnionymi brakami.

Wyniki znajdują się w pliku [inpainting.ipynb](inpainting.ipynb).
