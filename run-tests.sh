#!/usr/bin/env bash

set -o errexit

mkdir -p _build
g++ -I tiny-game-of-life test/test.cpp -c -Wno-write-strings -std=c++11 -o _build/test.o
g++ tiny-game-of-life/world.cpp -c -Wno-write-strings -std=c++11 -o _build/world.o
g++ _build/*.o -o _build/run-tests
./_build/run-tests
