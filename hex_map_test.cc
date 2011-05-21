#include "hex_map.hh"
#include "hex_map_generator.hh"

#include <iostream>
#include <ctime>

int main() {
    HexMap map( 20, 20 );
    HexMapGenerator gen( time( 0 ) );

    gen.generate( map );

    std::cout << map << std::endl;
}
