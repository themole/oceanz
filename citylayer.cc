#include "citylayer.hh"

#include <iostream>
#include <cstdlib>

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
    auto ci = cityInfo( x, y );
    for( auto cit = ci.begin(); cit != ci.end(); cit++ )
        if( cit->second == INSIDE )
            return true;
    return false;
}

City::city_id
CityLayer::insideCity( int x, int y ) const {
    auto ci = cityInfo( x, y );
    for( auto cit = ci.begin(); cit != ci.end(); cit++ ) {
        if( cit->second == INSIDE )
            return cit->first;
    }
    return 0;
}

bool
CityLayer::aroundCity( int x, int y ) const {
    auto ci = cityInfo( x, y );
    for( auto cit = ci.begin(); cit != ci.end(); cit++ ) {
        if( cit->second == AROUND )
            return true;
    }
    return false;
}

CityLayer::city_info
CityLayer::cityInfo( int x, int y ) const {
    if( x < 0 || y < 0 )
        return CityLayer::city_info();
    return _ci[ ( x % _sx ) + _sx * ( y % _sy ) ];
}

CityLayer::city_info
CityLayer::cityInfo( Position const & pos ) const {
    return cityInfo( pos.x(), pos.y() );
}

void
CityLayer::setCityInfo( int x, int y, City::city_id id, association_type at ) {
    if( x < 0 || y < 0 || x >= _sx || y >= _sy )
        return;
    _ci[ ( x % _sx ) + _sx * ( y % _sy ) ].erase( id );
    _ci[ ( x % _sx ) + _sx * ( y % _sy ) ].insert(
            std::pair< City::city_id, association_type > ( id, at ) );
}

void
CityLayer::setCityInfo( Position const & pos, City::city_id id, association_type t ) {
    setCityInfo( pos.x(), pos.y(), id, t );
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

std::map< City::city_id, City* > const &
CityLayer::cities() {
    return _cs;
}

void
CityLayer::newCity( int x, int y, std::string const & name ) {
    if( !cityAt( x, y ) ) {
        City* to_insert = new City( x, y, name + std::string( " " ) );
        char* str = new char[10];
        sprintf( str, "%d", to_insert->id() );
        to_insert->setName( to_insert->name() + str );
        delete[] str;
        _cs.insert( std::pair< City::city_id, City* >( to_insert->id(), to_insert ) );
        setCityInfo( x, y, to_insert->id(), INSIDE );    
        auto neighs = Position( x, y ).allNeighbors();
        for( auto nit = neighs.begin(); nit != neighs.end(); nit++ ) {
            setCityInfo( *nit, to_insert->id(), AROUND );
        }
    }
}


void
CityLayer::init( int, int ) {
}

void
CityLayer::uninit() {
}
