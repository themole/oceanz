#include "map.hh"
#include "map_generator.hh"

#include <iostream>
#include <fstream>
#include <cstdlib>


int main( int argc, char** argv ) {

    if( argc < 2 )
        std::cout << "usage: <cmd> <p> <f> <o> <a> <s>" << std::endl;

    Perlin p;
    for( int i = 1; i < argc; i++ ) {
        switch( i ) {
            case 1: p.setPersistence( atof(argv[i]) ); break;
            case 2: p.setFreq0( atof(argv[i]) ); break;
            case 3: p.setOctaves( atoi(argv[i]) ); break;
            case 4: p.setAmplitude( atof(argv[i]) ); break;
            case 5: p.setSeed( atol(argv[i]) ); break;
        }
    }

    Map map = Map( 128, 128 );
    MapGenerator mapgen;
    mapgen.setPerlin( p );

    mapgen.generate( map );

    map.save( "map.map" );


    Map map2 = Map();
    map2.load( "map.map" );

    std::ofstream out( "map_plot.data" );
    for( int y = 0; y < map2.sizeY(); y++ )
        for( int x = 0; x < map2.sizeX(); x++ )
            out << x << " " << y << " " << map2.height( x, y ) <<std::endl;
}

