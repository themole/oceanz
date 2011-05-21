#!/bin/bash
g++ -o noise noise.cc perlin.cc -Wall -Wextra -Werror -pedantic
g++ -o Noise Noise.cc perlin.cc -Wall -Wextra -Werror -pedantic
./noise > noise.data
./Noise > Noise.data
gnuplot "plot_noise.script"
evince noise.ps&
