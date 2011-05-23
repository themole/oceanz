#include "map.hh"

#include <iostream>

Map::Map()
    : _w( 0 ), _h( 0 ), _wl( 0 ), _t( 0 ) {}

Map::Map( int width, int height ) {
    if( width > 0 && height > 0 )
        _w = width, _h = height, _wl = 0,
        _t = new Tile[ _w * _h ];
    else
        _w = 0, _h = 0, _wl = 0,
        _t = 0;
}

Map::~Map() {
    if( _t )
        delete[] _t;
}

int
Map::width() const {
    return _w;
}

int
Map::height() const {
    return _h;
}

Tile&
Map::tile( int i ) {
    index_out_of_bounds_warning( i%_w, i/_w );
    return _t[i];
}

Tile&
Map::tile( int x, int y ) {
    index_out_of_bounds_warning( x, y );
    return _t[ ( x%_w ) + _w*( y%_h ) ];
}

Tile&
Map::operator[]( int i ) {
    return tile( i );
}

Tile&
Map::operator()( int x, int y ) {
    return tile( x, y );
}

int
Map::waterLevel() const {
    return _wl;
}


// debugging stuff
std::ostream&
operator<<( std::ostream& os, Map& map ) {
    for( int y = 0; y < map.height(); y++ ) {
        os << std::endl;
        for( int x = 0; x < map.width(); x++ ) {
            if( x == 0 )
                for( int k = y; k < map.width(); k++ )
                    os << "  ";
            os << map( x, y ).height() << "  ";
        }
    }
    os << std::endl;
    return os;
}

// private stuff
void
Map::index_out_of_bounds_warning( int x, int y ) const {
    if( x < 0 || x >= _w || y < 0 || y >= _h )
        std::cout << "WARNING: index out of bounds while acessing HexMap" << std::endl;
}
