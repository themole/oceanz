#!/bin/bash
g++ -o noise noise.cc perlin.cc -Wall -Wextra -Werror -pedantic
g++ -o Noise Noise.cc perlin.cc -Wall -Wextra -Werror -pedantic
g++ -o ./hex_tests/hex_distance_test ./hex_tests/hex_distance_test.cc
g++ -o hex_map_test hex_map_test.cc map.cc tile.cc perlin.cc map_generator.cc -Wall -Wextra -Werror -pedantic
g++ -o map_plot_test produce_map_plot_data.cc map.cc map_generator.cc perlin.cc tile.cc -Wall -Wextra -Werror -pedantic
g++ -o map_save_load_test map_save_load_test.cc map.cc map_generator.cc perlin.cc tile.cc -Wall -Wextra -Werror -pedantic

#./noise > noise.data
#./Noise > Noise.data
#gnuplot "plot_noise.script"
#evince noise.ps&
