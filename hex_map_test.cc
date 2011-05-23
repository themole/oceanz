#include "map.hh"
#include "map_generator.hh"

#include <iostream>
#include <ctime>

int main() {
    Map map( 20, 20 );
    MapGenerator gen( time( 0 ) );

    gen.generate( map );

    std::cout << map << std::endl;
}
