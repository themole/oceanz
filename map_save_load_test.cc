#include "map.hh"
#include "map_generator.hh"

#include <iostream>
#include <fstream>


int main() {
    Map map = Map( 128, 128 );
    MapGenerator mapgen;

    mapgen.generate( map );

    map.save( "map.map" );


    Map map2 = Map();
    map2.load( "map.map" );

    std::ofstream out( "map_plot.data" );
    for( int y = 0; y < map2.height(); y++ )
        for( int x = 0; x < map2.width(); x++ )
            out << x << " " << y << " " << map2( x, y ).height() <<std::endl;
}

