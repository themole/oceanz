#include "layer.hh"

Layer::Layer( unsigned width, unsigned height )
    : _sx( width ), _sy( height ) {
    if( _sx == 0 || _sy == 0 )
        _sx = 1, _sy = 1;
}

Layer::~Layer() {
}

unsigned
Layer::sizeX() const {
    return _sx;
}

unsigned
Layer::sizeY() const {
    return _sy;
}

unsigned
Layer::index( unsigned x, unsigned y ) const {
    return ( x%_sx ) + _sx * ( y%_sy );
}
