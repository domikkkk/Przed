#!/bin/bash
URL_TRAIN="http://data.vision.ee.ethz.ch/cvl/DIV2K/DIV2K_train_HR.zip"
URL_VALID="http://data.vision.ee.ethz.ch/cvl/DIV2K/DIV2K_valid_HR.zip"

DEST_TRAIN="./data/raw/train"
DEST_VALID="./data/raw/valid"
mkdir -p "$DEST_TRAIN"
mkdir -p "$DEST_VALID"

TEMP_DIR="/tmp/div2k"
mkdir -p "$TEMP_DIR"

wget -O "$TEMP_DIR/DIV2K_train_HR.zip" "$URL_TRAIN"
wget -O "$TEMP_DIR/DIV2K_valid_HR.zip" "$URL_VALID"

unzip "$TEMP_DIR/DIV2K_train_HR.zip" -d "$TEMP_DIR/train"
unzip "$TEMP_DIR/DIV2K_valid_HR.zip" -d "$TEMP_DIR/valid"

mv "$TEMP_DIR/train"/DIV2K_train_HR/* "$DEST_TRAIN/"
mv "$TEMP_DIR/valid"/DIV2K_valid_HR/* "$DEST_VALID/"

rm -rf "$TEMP_DIR"
