#include "hex_map.hh"

#include <iostream>

HexMap::HexMap()
    : _w( 0 ), _h( 0 ), _t( 0 ) {}

HexMap::HexMap( int width, int height ) {
    if( width > 0 && height > 0 )
        _w = width, _h = height,
        _t = new Tile[ _w * _h ];
    else
        _w = 0, _h = 0,
        _t = 0;
}

HexMap::~HexMap() {
    if( _t )
        delete[] _t;
}

int
HexMap::width() const {
    return _w;
}

int
HexMap::height() const {
    return _h;
}

Tile&
HexMap::tile( int i ) {
    index_out_of_bounds_warning( i%_w, i/_w );
    return _t[i];
}

Tile&
HexMap::tile( int x, int y ) {
    index_out_of_bounds_warning( x, y );
    return _t[ ( x%_w ) + _w*( y%_h ) ];
}

Tile&
HexMap::operator[]( int i ) {
    return tile( i );
}

Tile&
HexMap::operator()( int x, int y ) {
    return tile( x, y );
}


// debugging stuff
std::ostream&
operator<<( std::ostream& os, HexMap& map ) {
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
HexMap::index_out_of_bounds_warning( int x, int y ) const {
    if( x < 0 || x >= _w || y < 0 || y >= _h )
        std::cout << "WARNING: index out of bounds while acessing HexMap" << std::endl;
}
