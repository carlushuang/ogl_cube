#!/bin/sh

SRC="$(ls src/*.cc)"
TARGET=ogl_cube
CFLAGS="-Wall `pkg-config  --cflags glfw3`"
LDFLAGS="-lGL -lglfw -lm `pkg-config --libs glew` -lpthread"

rm -rf $TARGET *.o
g++ -std=c++11 $CFLAGS $SRC $LDFLAGS -o $TARGET
