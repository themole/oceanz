#include "tileframelayer.hh"

TileFrameLayer::TileFrameLayer( int sx, int sy )
    : Layer( sx, sy ) {
    
    _f = new tile_frame[ size() ];
}

TileFrameLayer::~TileFrameLayer() {
    delete[] _f;
}


Surface*
TileFrameLayer::frame( int x, int y ) {
    return frame( _f[ index( x, y ) ] );
}

Surface*
TileFrameLayer::frame( Position const & p ) {
    return frame( p.x(), p.y() );
}

Surface*
TileFrameLayer::frame( tile_frame id ) {
    return _frames[ id ];
}

void
TileFrameLayer::setFrame( tile_frame id, Surface* s ) {
    Surface *old = _frames[ id ];
    if( old != 0 )
        delete old;
    _frames[ id ] = s;
}


