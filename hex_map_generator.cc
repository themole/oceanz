#include "hex_map_generator.hh"

#include <cmath>
#include <iostream>

HexMapGenerator::HexMapGenerator( long seed ) {
    _p.setSeed( seed );
    _p.setAmplitude( 65536.f );
    _p.setPersistence( 0.5f );
    _p.setOctaves( 8 );
    _p.setFreq0( pow( .5f, 5.f ) );
}

HexMapGenerator::~HexMapGenerator() {}

void
HexMapGenerator::setPerlin( Perlin const & perlin ) {
    _p = perlin;
}

void
HexMapGenerator::generate( HexMap & map ) const {
    // TERRAIN GENERATION =============================== BEGIN
    // generates height map with heights in [-255, 255] ints
    float min = 0.f, max = 0.f;
    float noise = 0.f;

    for( int y = 0; y < map.height(); y++ )
        for( int x = 0; x < map.width(); x++ ) {
            noise = _p.Noise( x, y );
            if( noise < min ) min = noise;
            if( noise > max ) max = noise;

            map( x, y ).setHeight( noise );
        }
    std::cout << "min = " << min << ", max = " << max << std::endl;

    for( int y = 0; y < map.height(); y++ )
        for( int x = 0; x < map.width(); x++ ) {
            if( map( x,y ).height() > 0.f )
                map( x, y ).setHeight( map( x, y ).height() * 256.f / max );
            else 
                map( x, y ).setHeight( map( x, y ).height() * -256.f / min );
        }
    // TERRAIN GENERATION =============================== END 
}
