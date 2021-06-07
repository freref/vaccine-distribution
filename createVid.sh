#!/bin/bash

ENGINE_DIR='engine'
INI_DIR='./'
VIDEO='false'
OUTPUT='vidOut.mp4'

while getopts 'e:i:vo:' flag; do
  case "${flag}" in
    e) ENGINE_DIR="${OPTARG}" ;;
    i) INI_DIR="${OPTARG}" ;;
    v) VIDEO='true' ;;
    o) OUTPUT="${OPTARG}" ;;
  esac
done

#echo ${ENGINE_DIR}
#echo ${INI_DIR}
#echo "${INI_DIR}*.ini"

rm ${INI_DIR}/*.bmp
${ENGINE_DIR} ${INI_DIR}/*.ini
rm ${INI_DIR}/vidOut.mp4
if [ ${VIDEO} = 'true' ]; then
  ffmpeg -f image2 -pattern_type glob -framerate 2 -i "${INI_DIR}/*.bmp" "${OUTPUT}"
fi
#ffmpeg -f image2 -pattern_type glob -framerate 2 -i "${INI_DIR}*.bmp" 'vidOut.gif'
