#include "map.hh"

#include <iostream>
#include <fstream>
#include <string>

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

void
Map::save( std::string const & filename ) {
    std::ofstream file( filename.c_str(), std::ios::binary | std::ios::out);
    if( file.is_open() && _t ) {
        file.write( reinterpret_cast< char* >( &_w ), sizeof( int ) );
        file.write( reinterpret_cast< char* >( &_h ), sizeof( int ) );
        file.write( reinterpret_cast< char* >( _t ), _w * _h * sizeof( Tile ) );
    }
    file.close();
}

void
Map::load( std::string const & filename ) {
    if( _t )
        delete[] _t;

    std::ifstream file( filename.c_str(), std::ios::binary | std::ios::in );
    if( file.is_open() ) {
        file.read( reinterpret_cast< char* >( &_w ), sizeof( int ) );
        file.read( reinterpret_cast< char* >( &_h ), sizeof( int ) );
        _t = new Tile[ _w * _h ];
        file.read( reinterpret_cast< char* >( _t ), _w * _h * sizeof( Tile ) );
    }
    file.close();
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
