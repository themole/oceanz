#include "map.hh"
#include "map_generator.hh"
#include <iostream>
#include <iomanip>

int main() {
    Map map( 128, 128 );
    MapGenerator mapgen;
    mapgen.generate( map );

    for( int y = 0; y < map.height(); y++ )
        for( int x = 0; x < map.width(); x++ ) 
            std::cout << std::setfill(' ')
                      << std::setw(4) << x << "\t" 
                      << std::setw(4) << y << "\t"
                      << std::setw(4) << map( x, y ).height() << std::endl;
}
