#!/bin/sh


SRC="$(ls ./*.cc)"
TARGET=test_model
CFLAGS="-Wall `pkg-config  --cflags glfw3` `pkg-config --cflags assimp` -I./ -I../ -DTEST_MODEL"
LDFLAGS="-lGL -lglfw -lm `pkg-config --libs glew` `pkg-config --libs assimp` -lpthread"

rm -rf $TARGET *.o
g++ -std=c++11 $CFLAGS $SRC $LDFLAGS -o $TARGET
