#include "../perlin.hh"
#include "../worldmap.hh"
#include "../mapgenerator.hh"
#include "../maprenderer.hh"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

int main() {
    srand( time( 0 ) );
    long seed = rand();

    WorldMap map( 22, 22 );

    Perlin p;
    p.setPersistence( .35 );
    p.setOctaves( 8 );
    p.setAmplitude( 65536 );
    p.setFreq0( pow( .5f, 4.6 ) );
    p.setSeed( seed );
    MapGenerator mapgen;
    mapgen.setPerlin( p );

    mapgen.generateMap( map, 0.48f );

    MapRenderer mr( map );
    mr.printVertices();
}

