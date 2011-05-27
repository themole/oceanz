#include "heightmap.hh"

#include <iostream>

int main() {
    HeightMap hmap( 10, 10 );
    HeightMap hmap2;

    for( int i = 0; i < 10; i++ )
        for( int j = 0; j < 10; j++ )
            hmap.setHeight( i, j, i*j );

    hmap.save( "heightmap_test.hmap" );
    hmap2.load( "heightmap_test.hmap" );

    std::cout << hmap << hmap2 << std::endl;
}
