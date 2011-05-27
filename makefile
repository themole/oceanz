
CC = g++
FLAGS = -Wall -Wextra -Werror -pedantic -std=c++0x
OBJ = perlin.o map.o tile.o map_generator.o stock.o position.o heightlayer.o worldmap.o regionlayer.o


all: noise Noise stock_test heightlayer_test regionlayer_test

clean:
	rm -rf noise Noise hex_map_test map_plot_test map_save_load_test stock_test heightlayer_test regionlayer_test
	rm -rf *.o *.data *.map *.ps

.PHONY: all clean

noise: perlin.o noise.cc
	$(CC) -o noise perlin.o noise.cc $(FLAGS)

Noise: perlin.o Noise.cc
	$(CC) -o Noise perlin.o Noise.cc $(FLAGS)

stock_test: stock.o stock_test.cc
	$(CC) -o stock_test stock.o stock_test.cc $(FLAGS)

heightlayer_test: position.o heightlayer_test.cc heightlayer.o heightlayer.hh
	$(CC) -o heightlayer_test heightlayer.o position.o heightlayer_test.cc $(FLAGS)

regionlayer_test: position.o regionlayer.o heightlayer.o regionlayer_test.cc perlin.o map_generator.o
	$(CC) -o regionlayer_test regionlayer.o perlin.o heightlayer.o map_generator.o position.o regionlayer_test.cc $(FLAGS)

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

regionlayer.o: regionlayer.hh regionlayer.cc
	$(CC) -o regionlayer.o -c regionlayer.cc $(FLAGS) 

heightlayer.o: heightlayer.hh heightlayer.cc
	$(CC) -o heightlayer.o -c heightlayer.cc $(FLAGS)
	
worldmap.o: worldmap.hh worldmap.cc heightlayer.o regionlayer.o
	$(CC) -o worldmap.o -c worldmap.cc $(FLAGS)
