#include "heightlayer.hh"

#include <fstream>
#include <iomanip>

HeightLayer::HeightLayer() {
    init( 0, 0, 0 );
}

HeightLayer::HeightLayer( int width, int height ) {
    if( width > 0 && height > 0 )
        init( width, height, 0 );
    else
        init( 0, 0, 0 );
}

HeightLayer::~HeightLayer() {
    uninit();
}

bool HeightLayer::isNull() const {
    return ( _sx == 0 || _sy == 0 || _h == 0 );
}

int HeightLayer::sizeX() const {
    return _sx;
}

int HeightLayer::sizeY() const {
    return _sy;
}

HeightLayer::height_type HeightLayer::height( int x, int y ) const {
    if( !isNull() )
        return _h[( x % _sx ) + _sx * ( y % _sy )];
    else
        return height_type( 0 );
}

HeightLayer::height_type HeightLayer::height( Position const & pos ) const {
    return height( pos.x(), pos.y() );
}

void HeightLayer::setHeight( int x, int y, height_type height ) {
    if( isNull() )
        return;
    _h[( x % _sx ) + _sx * ( y % _sy )] = height;
}

void HeightLayer::setHeight( Position const & pos, height_type height ) {
    setHeight( pos.x(), pos.y(), height );
}

void HeightLayer::save( std::string const & filename ) {
    if( isNull() )
        return;

    std::ofstream file( filename.c_str(), std::ios::binary | std::ios::out );
    if( file.is_open() ) {
        file.write( "HeightMapFile", sizeof( "HeightMapFile" ) );
        file.write( reinterpret_cast< char* > ( &_sx ), sizeof(int) );
        file.write( reinterpret_cast< char* > ( &_sy ), sizeof(int) );
        file.write( reinterpret_cast< char* > ( _h ),
                    _sx * _sy * sizeof(height_type) );

        file.close();
    }
}

void HeightLayer::load( std::string const & filename ) {
    std::ifstream file( filename.c_str(), std::ios::binary | std::ios::in );
    if( file.is_open() ) {
        uninit();
        char buffer[sizeof( "HeightMapFile" )];
        file.read( buffer, sizeof( buffer ) );
        if( std::string( buffer ) == std::string( "HeightMapFile" ) ) {
            file.read( reinterpret_cast< char* > ( &_sx ), sizeof(int) );
            file.read( reinterpret_cast< char* > ( &_sy ), sizeof(int) );

            init( _sx, _sy, 0 );

            file.read( reinterpret_cast< char* > ( _h ),
                       _sx * _sy * sizeof(height_type) );
        }

        file.close();
    }
}

void HeightLayer::init( int sx, int sy, height_type h ) {
    if( sx > 0 && sy > 0 ) {
        _sx = sx, _sy = sy;
        _h = new height_type[sx * sy];
        for( int i = 0; i < sx * sy; i++ )
            _h[i] = h;
    } else
        _sx = 0, _sy = 0, _h = 0;
}

void HeightLayer::uninit() {
    if( !isNull() )
        delete[] _h;
}

std::ostream &
operator<<( std::ostream & os, HeightLayer const & hmap ) {
    for( int y = 0; y < hmap.sizeY(); y++ ) {
        os << std::endl;
        for( int x = 0; x < hmap.sizeX(); x++ ) {
            if( x == 0 )
                for( int k = y; k < hmap.sizeX(); k++ )
                    os << "  ";
            os << std::setfill( ' ' ) << std::setw( 4 ) << hmap.height( x, y )
                    << "  ";
        }
    }
    os << std::endl;
    return os;
}
