#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/kreds.png
ICON_DST=../../src/qt/res/icons/kreds.ico
convert ${ICON_SRC} -resize 16x16 kreds-16.png
convert ${ICON_SRC} -resize 32x32 kreds-32.png
convert ${ICON_SRC} -resize 48x48 kreds-48.png
convert kreds-16.png kreds-32.png kreds-48.png ${ICON_DST}

