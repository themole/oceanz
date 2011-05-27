
CC = g++
FLAGS = -Wall -Wextra -Werror -pedantic -std=c++0x
OBJ = perlin.o map.o tile.o city.o map_generator.o stock.o position.o heightmap.o worldmap.o regionmap.o


all: noise Noise hex_map_test map_plot_test map_save_load_test stock_test heightmap_test regionmap_test

clean:
	rm -rf noise Noise hex_map_test map_plot_test map_save_load_test stock_test heightmap_test
	rm -rf *.o *.data *.map *.ps

.PHONY: all clean

noise: perlin.o noise.cc
	$(CC) -o noise perlin.o noise.cc $(FLAGS)

Noise: perlin.o Noise.cc
	$(CC) -o Noise perlin.o Noise.cc $(FLAGS)

hex_map_test: $(OBJ) hex_map_test.cc
	$(CC) -o hex_map_test $(OBJ) hex_map_test.cc $(FLAGS)

map_plot_test: $(OBJ) produce_map_plot_data.cc
	$(CC) -o map_plot_test $(OBJ) produce_map_plot_data.cc $(FLAGS)

map_save_load_test: $(OBJ) map_save_load_test.cc
	$(CC) -o map_save_load_test $(OBJ) map_save_load_test.cc $(FLAGS)

stock_test: stock.o stock_test.cc
	$(CC) -o stock_test stock.o stock_test.cc $(FLAGS)

heightmap_test: position.o heightmap_test.cc heightmap.o heightmap.hh
	$(CC) -o heightmap_test heightmap.o position.o heightmap_test.cc $(FLAGS)

regionmap_test: position.o regionmap.o heightmap.o regionmap_test.cc perlin.o map_generator.o
	$(CC) -o regionmap_test regionmap.o perlin.o heightmap.o map_generator.o position.o regionmap_test.cc $(FLAGS)

perlin.o: perlin.hh perlin.cc
	$(CC) -o perlin.o -c perlin.cc $(FLAGS)

tile.o: tile.hh tile.cc
	$(CC) -o tile.o -c tile.cc $(FLAGS)

map.o: map.hh map.cc
	$(CC) -o map.o -c map.cc $(FLAGS)

stock.o: stock.hh stock.cc
	$(CC) -o stock.o -c stock.cc $(FLAGS)

city.o: city.hh city.cc
	$(CC) -o city.o -c city.cc $(FLAGS)

position.o: position.hh position.cc
	$(CC) -o position.o -c position.cc $(FLAGS)

map_generator.o: map_generator.hh map_generator.cc
	$(CC) -o map_generator.o -c map_generator.cc $(FLAGS)

regionmap.o: regionmap.hh regionmap.cc
	$(CC) -o regionmap.o -c regionmap.cc $(FLAGS) 

heightmap.o: heightmap.hh heightmap.cc
	$(CC) -o heightmap.o -c heightmap.cc $(FLAGS)
	
worldmap.o: worldmap.hh worldmap.cc heightmap.o regionmap.o
	$(CC) -o worldmap.o -c worldmap.cc $(FLAGS)