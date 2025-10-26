

# #!/bin/bash
URL_TRAIN="https://www.repository.cam.ac.uk/bitstreams/3e871fb5-0cb9-4376-913d-5f5e5006a5c4/download"

DEST_TRAIN="./data"
mkdir -p "$DEST_TRAIN"

TEMP_DIR="/tmp/sihdr"
mkdir -p "$TEMP_DIR"

wget -O "$TEMP_DIR/reference.zip" "$URL_TRAIN"

unzip "$TEMP_DIR/reference.zip" -d "$TEMP_DIR"

mv "$TEMP_DIR/sihdr/sihdr/reference" "$DEST_TRAIN/"

rm -rf "$TEMP_DIR"
