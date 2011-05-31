#include "../regionlayer.hh"
#include "../heightlayer.hh"
#include "../mapgenerator.hh"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

int main() {
    srand( time( 0 ) );
    long seed = rand();
    HeightLayer hmap( 128, 128 );
    Perlin p;
    p.setPersistence( .35 );
    p.setOctaves( 8 );
    p.setAmplitude( 65536 );
    p.setFreq0( pow( .5f, 4.6 ) );
    p.setSeed( seed );
    MapGenerator mapgen;
    mapgen.setPerlin( p );

    mapgen.generate( hmap );
    RegionLayer rl( hmap );
    //    while( gm.regionSize( gm.greatestRegion( GroupMap::COAST ) ) < 900 ) {
    //        p.setSeed( rand() );
    //        mapgen.setPerlin( p );
    //        mapgen.generate( hmap );
    //        gm = GroupMap( hmap );
    //    }

    std::cout << "greatestCost = " << rl.greatestRegion( COAST )
            << " with "
            << rl.regionSize( rl.greatestRegion( COAST ) )
            << " tiles." << std::endl << std::endl;
    std::cout << "seed = " << seed << std::endl << std::endl;
}
