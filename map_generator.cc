#include "map_generator.hh"

#include <cmath>

#ifndef PI
#define PI 3.141592653589
#endif

MapGenerator::MapGenerator( long seed ) {
    _p.setSeed( seed );
    _p.setAmplitude( 65536.f );
    _p.setPersistence( 0.26f );
    _p.setOctaves( 8 );
    _p.setFreq0( pow( .5f, 6.f ) );
}

MapGenerator::~MapGenerator() {
}

void MapGenerator::setPerlin( Perlin const & perlin ) {
    _p = perlin;
}

#include <vector>

void MapGenerator::generate( HeightLayer & hmap ) const {
    float min = 0.f, max = 0.f;
    float noise = 0.f;

    // this is (y,x) later
    std::vector< std::vector< float > > tmp;

    for( int y = 0; y < hmap.sizeY(); y++ ) {
        tmp.push_back( std::vector< float >() );
        for( int x = 0; x < hmap.sizeX(); x++ ) {
            noise = _p.Noise( ( hmap.sizeY() - y + 2 * x ) * cos( PI / 6.f ),
                              ( 2 * y ) * sin( PI / 6.f ) + 1.f );
            if( noise < min )
                min = noise;
            if( noise > max )
                max = noise;

            tmp[y].push_back( noise );
        }
    }

    float w = min + .48f * ( max - min );

    for( int y = 0; y < hmap.sizeY(); y++ )
        for( int x = 0; x < hmap.sizeX(); x++ ) {
            if( tmp[y][x] > w )
                hmap.setHeight( x,
                                y,
                                ( tmp[y][x] - w ) / ( max - w )
                                        * HeightLayer::HEIGHT_MAX );
            else
                hmap.setHeight( x,
                                y,
                                ( tmp[y][x] - w ) / ( min - w )
                                        * HeightLayer::HEIGHT_MIN );
        }
}

