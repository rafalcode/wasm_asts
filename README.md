# wasm_asts
Game of Asteroids for WASM

## credits
this medium webpage
https://medium.com/swlh/i-made-a-game-in-c-run-in-a-web-browser-and-so-can-you-2911b9fe2368
written by Vitor Leal
However the main c code I think is from
https://github.com/flightcrank/asteroids

## to compile
Well, better said "transpile" because emscripten will compile to WASM bytecode
emcc -o asts.html *.c -Wall -g -lm -s USE_SDL=2
emcc being the "compiler"
it create asts.html and asts.wasm

## Run a webserver
In Archlinux you can run 
python -m RangeHTTPServer 8080
from the directory where the code is
then visit
localhost:8080/asts.html
in your browser

## RF comments
- the "canvas" center is given pixel coords (0,0) so that's why you see SCREENWIDTH/2 so often.
- VERTS is not explained but it must surely means VERTEX/VERTICES
- the ship and asteroids vertices are given small values such as .1, .4 etc. this is because they are viewed as "object vertices", they need to be mu
- player/ship and asteroid vertices are rendered "world vertices" or "screen vertices via multiplication.
- the "alive" marker refers to the object being on the screen, so a certain number are created but only a few are shown.
- note its SDL v1.2 not the more usual SDL v2 BUT -s USE_SDL=2?

The vector type was just the (x,y) float, and was called vector because it has a notional origin at 0,0. I prefer to call this a "Point Vector" rather
than vector, which for me is an array. And, in truth, it pretty much is just a point.
