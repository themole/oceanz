#include "../worldmap.hh"
#include "../mapgenerator.hh"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

int main() {
    srand( time( 0 ) );
    long seed = rand();

    WorldMap map( 20, 20 );
    HeightLayer *hl = new HeightLayer( 20, 20 );

    map.setHeightLayer( hl );

    Perlin p;
    p.setPersistence( .35 );
    p.setOctaves( 8 );
    p.setAmplitude( 65536 );
    p.setFreq0( pow( .5f, 4.6 ) );
    p.setSeed( seed );
    MapGenerator mapgen;
    mapgen.setPerlin( p );

    mapgen.generateMap( map, 0.48f );
    //    while( gm.regionSize( gm.greatestRegion( GroupMap::COAST ) ) < 900 ) {
    //        p.setSeed( rand() );
    //        mapgen.setPerlin( p );
    //        mapgen.generate( hmap );
    //        gm = GroupMap( hmap );
    //    }
    map.regionLayer()->print();

    RegionLayer *rl = map.regionLayer();

    std::cout << "greates WATER = " << rl->greatestRegion( WATER )->id()
            << " with "
            << rl->greatestRegion( WATER )->size()
            << " tiles." << std::endl << std::endl;
    std::cout << "greates  LAND = " << rl->greatestRegion( LAND )->id()
            << " with "
            << rl->greatestRegion( LAND )->size()
            << " tiles." << std::endl << std::endl;
    std::cout << "seed = " << seed << std::endl << std::endl;
}
