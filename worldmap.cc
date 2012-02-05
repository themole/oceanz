#include "worldmap.hh"

WorldMap::WorldMap( unsigned sx, unsigned sy )
    : _sx( sx ), _sy( sy ),
      _hl( 0 ),
      _rl( 0 ),
      _cl( 0 ) {
    if( sx == 0 || sy == 0 )
        _sx = 1, _sy = 1;
}

WorldMap::~WorldMap() {
    if( _hl != 0 )
        delete _hl;
    if( _rl != 0 )
        delete _rl;
    if( _cl != 0 )
        delete _cl;
    _hl = 0, _rl = 0, _cl = 0;
}

int
WorldMap::sizeX() const {
    return _sx;
}

int
WorldMap::sizeY() const {
    return _sy;
}

HeightLayer *
WorldMap::heightLayer() {
    return _hl;
}

RegionLayer *
WorldMap::regionLayer() {
    return _rl;
}

CityLayer *
WorldMap::cityLayer() {
    return _cl;
}

void
WorldMap::setHeightLayer( HeightLayer * hl ) {
    if( hl->sizeX() == _sx && hl->sizeY() == _sy ) {
        if( _hl != 0 )
            delete _hl;
        _hl = hl;
    }
}

void
WorldMap::setRegionLayer( RegionLayer * rl ) {
    if( rl->sizeX() == _sx && rl->sizeY() == _sy ) {
        if( _rl != 0 )
            delete _rl;
        _rl = rl;
    }
}
void
WorldMap::setCityLayer( CityLayer * cl ) {
    if( cl->sizeX() == _sx && cl->sizeY() == _sy ) {
        if( _cl != 0 )
            delete _cl;
        _cl = cl;
    }
}

HeightLayer::height_type
WorldMap::height( int x, int y ) {
    return _hl->height( x, y );
}

HeightLayer::height_type
WorldMap::height( Position const & pos ) {
    return height( pos.x(), pos.y() );
}

TerrainRegion *
WorldMap::region( int x, int y ) {
    if( _rl != 0 )
        return _rl->region( x, y );
    else
        return 0;
}

TerrainRegion *
WorldMap::region( Position const & pos ) {
    return region( pos.x(), pos.y() );
}

City*
WorldMap::city( int x, int y ) {
    return _cl->city( x, y );
}

City*
WorldMap::city( Position const & pos ) {
    return city( pos.x(), pos.y() );
}
