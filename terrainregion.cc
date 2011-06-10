#include "terrainregion.hh"

unsigned TerrainRegion::current_id = 0;

TerrainRegion::TerrainRegion( region_type type )
    : _id( TerrainRegion::current_id++ ), 
      _sz( 0 ),
      _tp( type ) {
}

TerrainRegion::TerrainRegion( TerrainRegion const & r ) 
    : _id( r._id ),
      _sz( r._sz ),
      _tp( r._tp ) {

    _c.insert( r._c.begin(), r._c.end() );
}

TerrainRegion::~TerrainRegion() {
    // not responible for anything
}

unsigned
TerrainRegion::id() const {
    return _id;
}

unsigned
TerrainRegion::size() const {
    return _sz;
}

unsigned char
TerrainRegion::type() const {
    return _tp;
}

bool
TerrainRegion::is( region_type type ) const {
    return (_tp & type) == type;
}

std::set< TerrainRegion * >
TerrainRegion::connected() const {
    return _c;
}

void
TerrainRegion::setType( region_type type ) {
    _tp |= type;
}

void
TerrainRegion::unsetType( region_type type ) {
    _tp &= !type;
}

void
TerrainRegion::setSize( unsigned size ) {
    _sz = size;
}

void
TerrainRegion::setConnected( TerrainRegion * r ) {
    if( r == 0 )
        return;
    if( _id != r->id() ) 
        _c.insert( r );
}

void
TerrainRegion::unsetConnected( TerrainRegion * r ) {
    _c.erase( r );
}

void
TerrainRegion::incrementSize() {
    _sz++;
}

void
TerrainRegion::decrementSize() {
    _sz--;
}

bool
TerrainRegion::operator<( TerrainRegion const & rhs ) const {
    return _id < rhs._id;
}

bool
TerrainRegion::operator==( TerrainRegion const & rhs ) const {
    return _id == rhs._id;
}

std::ostream &
operator<<( std::ostream & os, TerrainRegion & r ) {
    if( r.is( WATER ) ) os << "W";
    if( r.is( LAND ) )  os << "L";
    if( r.is( COAST ) ) os << "c";
    return os << r.id();
}
