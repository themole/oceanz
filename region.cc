#include "region.hh"

Region::Region( unsigned id, RegionType t )
    : _id( id ), _sz( 0 ), _t( t ) {
}

Region::~Region() {
}

unsigned
Region::size() const {
    return _sz;
}

unsigned
Region::id() const {
    return _id;
}

RegionType
Region::type() const {
    return _t;
}

bool
Region::isLand() const {
    return _t == LAND;
}

bool
Region::isWater() const {
    return _t == WATER;
}

bool
Region::is( RegionType t ) const {
    return _t == t;
}

Region
Region::operator+( Region const & rhs ) const {
    if( _t == rhs._t )
        return Region( ( _id < rhs._id ) ? _id : rhs._id,
                       _t );
    else
        return Region( (unsigned) -1, NO_REGION );
}

Region &
Region::operator=( Region const & rhs ) {
    _id = rhs._id;
    _sz = rhs._sz;
    _t = rhs._t;
    return *this;
}
