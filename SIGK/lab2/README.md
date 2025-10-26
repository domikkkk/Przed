# LAB 2

## Pobieranie danych:
```sh
sudo chmod +x download.sh
./download.sh

# Download required dependencies
pip install -r requirements.txt

# Prepare data for scalling and inpainting tasks
python preparing_data.py
```

## Zadanie

Projekt miał na celu próbę odtworzenia modelu SelfTMO z artykułu [Learning a self-supervised tone mapping operator via feature
contrast masking loss](https://arxiv.org/pdf/2110.09866) z użyciem zbioru danych [SI-HDR](https://www.repository.cam.ac.uk/items/c02ccdde-db20-4acd-8941-7816ef6b7dc7).


Wyniki znajdują się w [note.ipynb](note.ipynb).
