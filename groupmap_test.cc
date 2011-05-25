#include "groupmap.hh"
#include "heightmap.hh"
#include "map_generator.hh"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    srand( time( 0 ) );
    HeightMap<short> hmap( 128, 128 );
    Perlin p;
    p.setPersistence( .35 );
    p.setOctaves( 8 );
    p.setAmplitude( 65536 );
    p.setFreq0( 0.03125 );
    p.setSeed( rand() );
    MapGenerator mapgen;
    mapgen.setPerlin( p );
    mapgen.generate( hmap );

    GroupMap gm( hmap );
    std::cout << "greatestCost = "
              << gm.greatestGroup( GroupMap::COAST )
              << " with "
              << gm.groupSize( gm.greatestGroup( GroupMap::COAST ))
              << " tiles." << std::endl;
    
}
