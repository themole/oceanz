
CC = g++
FLAGS = -Wall -Wextra -Werror -pedantic -std=c++0x
OBJ = perlin.o map.o tile.o city.o map_generator.o


all: noise Noise hex_map_test map_plot_test map_save_load_test stock_test

clean:
	rm -rf noise Noise hex_map_test map_plot_test map_save_load_test stock_test
	rm -rf *.o *.data *.map *.ps

.PHONY: all clean

noise: $(OBJ) noise.cc
	$(CC) -o noise $(OBJ) noise.cc $(FLAGS)

Noise: $(OBJ) Noise.cc
	$(CC) -o Noise $(OBJ) Noise.cc $(FLAGS)

hex_map_test: $(OBJ) hex_map_test.cc
	$(CC) -o hex_map_test $(OBJ) hex_map_test.cc $(FLAGS)

map_plot_test: $(OBJ) produce_map_plot_data.cc
	$(CC) -o map_plot_test $(OBJ) produce_map_plot_data.cc $(FLAGS)

map_save_load_test: $(OBJ) map_save_load_test.cc
	$(CC) -o map_save_load_test $(OBJ) map_save_load_test.cc $(FLAGS)

stock_test: stock.o stock_test.cc
	$(CC) -o stock_test stock.o stock_test.cc $(FLAGS)

perlin.o: perlin.hh perlin.cc
	$(CC) -o perlin.o -c perlin.cc $(FLAGS)

tile.o: tile.hh tile.cc
	$(CC) -o tile.o -c tile.cc $(FLAGS)

map.o: map.hh map.cc
	$(CC) -o map.o -c map.cc $(FLAGS)

city.o: city.hh city.cc
	$(CC) -o city.o -c city.cc $(FLAGS)

stock.o: stock.hh stock.cc
	$(CC) -o stock.o -c stock.cc $(FLAGS)

map_generator.o: map_generator.hh map_generator.cc
	$(CC) -o map_generator.o -c map_generator.cc $(FLAGS)
