#!/bin/bash
# uses emscripting to compile "asts" the game of asteroids for WASM
/usr/lib/emscripten/emcc -o asts.html *.c -Wall -g -s USE_SDL=2
