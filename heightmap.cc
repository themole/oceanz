#include "heightmap.hh"

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
    return height_type( 0 );
}

template< typename T >
T
HeightMap<T>::height( Position const & pos ) const {
    return height_type( 0 );
}

template< typename T >
void
HeightMap<T>::save( std::string const & filename ) {
}

template< typename T >
void
HeightMap<T>::load( std::string const & filename ) {
}

template< typename T >
void
HeightMap<T>::init( int sx, int sy, T h ) {

}

template< typename T >
void
HeightMap<T>::uninit() {
}

template< typename T >
std::ostream &
operator<<( std::ostream & os, HeightMap< T > const & hmap ) {
    return os;
}
