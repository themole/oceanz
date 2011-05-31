#include "citylayer.hh"

#include <iostream>

CityLayer::CityLayer( int sx, int sy )
    : _sx( sx ), _sy( sy ) {
    if( _sx <= 0 || _sy <= 0 )
        _sx = 1, _sy = 1;
}

CityLayer::~CityLayer() {
    // delete all cities
    for( auto it = _c.begin(); it != _c.end(); it++ )
        if( it->first != 0 )
            delete it->first;
}

City*
CityLayer::city( int x, int y ) {
    Position p = Position( x, y );
    for( auto it = _c.begin(); it != _c.end(); it++ )
        if( it->second == p )
            return it->first;
    return 0;
}

void
CityLayer::setCity( int x, int y, City* const c ) {
    _c.insert( std::pair< City*, Position >( c, Position( x, y ) ) );
}
