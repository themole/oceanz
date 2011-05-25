#include "groupmap.hh"
#include "heightmap.hh"
#include "map_generator.hh"
#include <iostream>

int main() {
    HeightMap<short> hmap( 64, 64 );
    Perlin p;
    p.setPersistence( .3 );
    p.setOctaves( 8 );
    p.setAmplitude( 65536 );
    p.setFreq0( 0.125 );
    p.setSeed( 0 );
    MapGenerator mapgen;
    mapgen.setPerlin( p );
    mapgen.generate( hmap );
    std::cout << hmap;

    GroupMap gm( hmap );
}
