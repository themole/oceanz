#include "groupmap.hh"
#include "heightmap.hh"
#include "map_generator.hh"
#include <iostream>

int main() {
    HeightMap<short> hmap( 128, 128 );
    Perlin p;
    p.setPersistence( .4 );
    p.setOctaves( 8 );
    p.setAmplitude( 65536 );
    p.setFreq0( 0.06125 );
    p.setSeed( 0 );
    MapGenerator mapgen;
    mapgen.setPerlin( p );
    mapgen.generate( hmap );

    GroupMap gm( hmap );
    std::cout << "greatestCost = " << gm.greatestGroup( GroupMap::COAST ) << std::endl;
}
