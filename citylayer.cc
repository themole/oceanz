#include "citylayer.hh"

#include <iostream>

CityLayer::CityLayer( int sx, int sy )
    : _sx( sx ), _sy( sy ) {
    if( _sx <= 0 || _sy <= 0 )
        _sx = 1, _sy = 1;

    _ci = new city_info[ _sx * _sy ];
}

CityLayer::~CityLayer() {
    if( _ci != 0 )
        delete[] _ci;
    // self responsible for city creation ... only saving pointers ... so need to destruct
    for( auto cit = _cs.begin(); cit != _cs.end(); cit++ ) 
        if( cit->second != 0 ) delete cit->second;
}

int
CityLayer::sizeX() const {
    return _sx;
}

int
CityLayer::sizeY() const {
    return _sy;
}

bool
CityLayer::cityAt( int x, int y ) const {
    return !cityInfo( x, y ).empty();
}

CityLayer::city_info
CityLayer::cityInfo( int x, int y ) const {
    return _ci[ ( x % _sx ) + _sx * ( y % _sy ) ];
}

CityLayer::city_info
CityLayer::cityInfo( Position const & pos ) const {
    return cityInfo( pos.x(), pos.y() );
}

City*
CityLayer::city( int x, int y ) {
    city_info ci = cityInfo( x, y );
    for( auto cit = ci.begin(); cit != ci.end(); cit++ ) 
        if( cit->second == INSIDE ) return city( cit->first );
    return 0;
}

City*
CityLayer::city( Position const & pos ) {
    return city( pos.x(), pos.y() );
}

City*
CityLayer::city( City::city_id cid ) {
    return _cs.find( cid )->second;
}

void
CityLayer::newCity( int x, int y, std::string const & name ) {
    if( !cityAt( x, y ) ) {
        City* to_insert = new City( name );
        _cs.insert( std::pair< City::city_id, City* >( to_insert->id(), to_insert ) );
    }
}

void
CityLayer::init( int, int ) {
}

void
CityLayer::uninit() {
}
