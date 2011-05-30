#include "citylayer.hh"

#include <iostream>

CityLayer::CityLayer( unsigned sx, unsigned sy )
    : Layer( sx, sy ) {
        null = 0;
}

CityLayer::~CityLayer() {
    // delete all cities
    for( auto it = _c.begin(); it != _c.end(); it++ )
        if( it->first != 0 )
            delete it->first;
}

CityLayer::value_type const &
CityLayer::operator()( unsigned i ) {
    return operator()( position( i ) );
}

CityLayer::value_type const &
CityLayer::operator()( unsigned x, unsigned y ) {
    return operator()( Position( x, y ) );
}

CityLayer::value_type const &
CityLayer::operator()( Position const & p ) {

    for( auto it = _c.begin(); it != _c.end(); it++ )
        if( it->second == p )
            return it->first;
    return null;
}

void
CityLayer::operator()( unsigned i, City* const & c ) {
    operator()( position( i ), c );
}

void
CityLayer::operator()( unsigned x, unsigned y, City* const & c ) {
    operator()( Position( x, y ), c );
}

void
CityLayer::operator()( Position const & p, City* const & c ) {
    auto it = _c.find( c );
    if( it == _c.end() )
        _c.insert( std::pair< City*, Position >( c, p ) );
}

bool
CityLayer::valid() const  {
    return true;
}
