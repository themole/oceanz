#include "region.hh"

unsigned Region::current_id = 0;

Region::Region( region_type type )
    : _id( Region::current_id++ ), 
      _sz( 0 ),
      _tp( type ) {
}

Region::Region( Region const & r ) 
    : _id( r._id ),
      _sz( r._sz ),
      _tp( r._tp ) {

    _c.insert( r._c.begin(), r._c.end() );
}

Region::~Region() {
    // not responible for anything
}

unsigned
Region::id() const {
    return _id;
}

unsigned
Region::size() const {
    return _sz;
}

unsigned char
Region::type() const {
    return _tp;
}

bool
Region::is( region_type type ) const {
    return (_tp & type) == type;
}

std::set< Region * >
Region::connected() const {
    return _c;
}

void
Region::setType( region_type type ) {
    _tp |= type;
}

void
Region::unsetType( region_type type ) {
    _tp &= !type;
}

void
Region::setSize( unsigned size ) {
    _sz = size;
}

void
Region::setConnected( Region * r ) {
    if( r == 0 )
        return;
    if( _id != r->id() ) 
        _c.insert( r );
}

void
Region::unsetConnected( Region * r ) {
    _c.erase( r );
}

void
Region::incrementSize() {
    _sz++;
}

void
Region::decrementSize() {
    _sz--;
}

bool
Region::operator<( Region const & rhs ) const {
    return _id < rhs._id;
}

bool
Region::operator==( Region const & rhs ) const {
    return _id == rhs._id;
}

std::ostream &
operator<<( std::ostream & os, Region & r ) {
    if( r.is( WATER ) ) os << "W";
    if( r.is( LAND ) )  os << "L";
    if( r.is( COAST ) ) os << "c";
    return os << r.id();
}
