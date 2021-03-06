#!/bin/sh

SRC="$(ls src/*.cc) $(ls src/model/*.cc)"
TARGET=ogl_cube
CFLAGS="-Wall `pkg-config  --cflags glfw3` `pkg-config --cflags assimp` -Isrc -Isrc/model"
LDFLAGS="-lGL -lglfw -lm `pkg-config --libs glew` `pkg-config --libs assimp` -lpthread"

rm -rf $TARGET *.o
g++ -std=c++11 $CFLAGS $SRC $LDFLAGS -o $TARGET
