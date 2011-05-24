#include "heightmap.hh"

#include <fstream>

template< typename T >
HeightMap<T>::HeightMap() {
    init( 0, 0, 0 );
}

template< typename T >
HeightMap<T>::HeightMap( int width, int height ) {
    if( width > 0 && height > 0 )
        init( width, height, 0 );
    else
        init( 0, 0, 0 );
}

template< typename T >
HeightMap<T>::~HeightMap() {
    uninit();
}

template< typename T >
bool
HeightMap<T>::isNull() const {
    return ( _sx == 0 || _sy == 0 || _h == 0 );
}

template< typename T >
int
HeightMap<T>::sizeX() const {
    return _sx;
}

template< typename T >
int
HeightMap<T>::sizeY() const {
    return _sy;
}

template< typename T >
T
HeightMap<T>::height( int x , int y ) const {
    if( !isNull() )
        return _h[ ( x%_sx ) + _sx * ( y%_sy ) ];
    else
        return height_type( 0 );
}

template< typename T >
T
HeightMap<T>::height( Position const & pos ) const {
    return height( pos.x(), pos.y() );
}

template< typename T >
void
HeightMap<T>::setHeight( int x, int y, T height ) {
    if( isNull() )
        return;
    _h[ ( x%_sx ) + _sx * ( y%_sy ) ] = height;
}

template< typename T >
void
HeightMap<T>::setHeight( Position const & pos, T height ) {
    setHeight( pos.x(), pos.y(), height );
}

template< typename T >
void
HeightMap<T>::save( std::string const & filename ) {
    if( isNull() ) return;

    std::ofstream file( filename.c_str(),
                        std::ios::binary | std::ios::out );
    if( file.is_open() ) {
        file.write( "HeightMapFile", sizeof("HeightMapFile") );
        file.write( reinterpret_cast< char* >( &_sx ),
                    sizeof( int ) );
        file.write( reinterpret_cast< char* >( &_sy ),
                    sizeof( int ) );
        file.write( reinterpret_cast< char* >( _h ),
                    _sx * _sy * sizeof( T ) );

        file.close();
    }
}

template< typename T >
void
HeightMap<T>::load( std::string const & filename ) {
    std::ifstream file( filename.c_str(),
                        std::ios::binary | std::ios::in );
    if( file.is_open() ) {
        uninit();
        char buffer[ sizeof( "HeightMapFile" ) ];
        file.read( buffer, sizeof( buffer ) );
        if( std::string( buffer ) == std::string( "HeightMapFile" ) ) {
            file.read( reinterpret_cast< char* >( &_sx ),
                       sizeof( int ) );
            file.read( reinterpret_cast< char* >( &_sy ),
                       sizeof( int ) );

            init( _sx, _sy, 0 );

            file.read( reinterpret_cast< char* >( _h ),
                       _sx * _sy * sizeof( T ) );
        }

        file.close();
    }
}

template< typename T >
void
HeightMap<T>::init( int sx, int sy, T h ) {
    if( sx > 0 && sy > 0 ) {
        _sx = sx, _sy = sy;
        _h = new T[ sx * sy ];
        for( int i = 0; i < sx*sy; i++ )
            _h[i] = h;
    } else
        _sx = 0, _sy = 0, _h = 0;
}

template< typename T >
void
HeightMap<T>::uninit() {
    if( !isNull() )
        delete[] _h;
}

template< typename T >
std::ostream &
operator<<( std::ostream & os, HeightMap< T > const & hmap ) {
    return os;
}
