#!/bin/sh

x86_64-w64-mingw32-gcc ./main.c ./bookFunc.c ./ui_win.c ./ascii.c -std=c89 -lm -Wall -o win64_output.exe