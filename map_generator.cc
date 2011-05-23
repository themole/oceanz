#include "map_generator.hh"

#include <cmath>

MapGenerator::MapGenerator( long seed ) {
    _p.setSeed( seed );
    _p.setAmplitude( 65536.f );
    _p.setPersistence( 0.6f );
    _p.setOctaves( 8 );
    _p.setFreq0( pow( .5f, 6.f ) );
}

MapGenerator::~MapGenerator() {}

void
MapGenerator::setPerlin( Perlin const & perlin ) {
    _p = perlin;
}

void
MapGenerator::generate( Map & map ) const {
    generateTerrain( map );
}

void
MapGenerator::generateTerrain( Map & map ) const {
    float min = 0.f, max = 0.f;
    float noise = 0.f;

    for( int y = 0; y < map.height(); y++ )
        for( int x = 0; x < map.width(); x++ ) {
            noise = _p.Noise( x, y );
            if( noise < min ) min = noise;
            if( noise > max ) max = noise;

            map( x, y ).setHeight( noise );
        }

    for( int y = 0; y < map.height(); y++ )
        for( int x = 0; x < map.width(); x++ ) {
            if( map( x, y ).height() > map.waterLevel() )
                map( x, y ).setHeight( map( x, y ).height() * 256.f / max );
            else if( map( x, y ).height() < map.waterLevel() )
                map( x, y ).setHeight( map( x, y ).height() * -256.f / min );
            else
                map( x, y ).setHeight( 0 );
        }
}

void
MapGenerator::generateCities( Map & map ) const {
    // TODO: find some way to do this
    map = map;
}
