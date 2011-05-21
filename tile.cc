#include "tile.hh"

Tile::Tile( int height ) 
    : _h( height ) { }
    
int
Tile::height() const {
    return _h;
}

void
Tile::setHeight( int height ) {
    _h = height;
}
