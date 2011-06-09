#include "layer.hh"

Layer::Layer( int sx, int sy )
    : _sx( sx ), _sy( sy ) {
    
    if( _sx <= 0 || _sy <= 0 )
        _sx = 1, _sy = 1;
}

Layer::~Layer() {
}

int
Layer::sizeX() const {
    return _sx;
}

int
Layer::sizeY() const {
    return _sy;
}

int
Layer::size() const {
    return _sx * _sy;
}

int
Layer::index( int x, int y ) const {
    return ( x % _sx ) + _sx * ( y % _sy );
}
