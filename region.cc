#include "region.hh"

unsigned Region::current_id = 0;

Region::Region( region_type type )
    : _id( Region::current_id++ ), 
      _sz( 0 ),
      _tp( type ) {
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

region_type
Region::type() const {
    return _tp;
}

std::set< Region* >
Region::connected() const {
    return _c;
}

void
Region::setType( region_type type ) {
    _tp = type;
}

void
Region::setSize( unsigned size ) {
    _sz = size;
}

void
Region::setConnected( Region* r ) {
    if( r->id() != _id )
        _c.insert( r );
}

void
Region::incrementSize() {
    _sz++;
}

void
Region::decrementSize() {
    _sz--;
}
