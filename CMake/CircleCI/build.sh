#!/bin/sh

script_dir="`cd $(dirname $0); pwd`"

docker build -t commontk/ctk-test:opengl-qt4 $script_dir -f Dockerfile-qt4
docker build -t commontk/ctk-test:opengl-qt5 $script_dir -f Dockerfile-qt5
