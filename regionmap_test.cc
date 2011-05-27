#include "regionmap.hh"
#include "heightmap.hh"
#include "map_generator.hh"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

int main() {
    srand( time( 0 ) );
    HeightMap hmap( 256, 128 );
    Perlin p;
    p.setPersistence( .5 );
    p.setOctaves( 12 );
    p.setAmplitude( 65536 );
    p.setFreq0( pow( .5f, 6.5 ) );
    p.setSeed( rand() );
    MapGenerator mapgen;
    mapgen.setPerlin( p );

    mapgen.generate( hmap );
    RegionMap gm( hmap );
    //    while( gm.regionSize( gm.greatestRegion( GroupMap::COAST ) ) < 900 ) {
    //        p.setSeed( rand() );
    //        mapgen.setPerlin( p );
    //        mapgen.generate( hmap );
    //        gm = GroupMap( hmap );
    //    }

    std::cout << "greatestCost = " << gm.greatestRegion( RegionMap::COAST )
            << " with "
            << gm.regionSize( gm.greatestRegion( RegionMap::COAST ) )
            << " tiles." << std::endl;

}
