#include "building.hh"

Building::Building()
    : _level( 1 ) {
}

Building::~Building() {
}

unsigned
Building::level() const {
    return _level;
}

Stock const
Building::upgradeCost( unsigned ) {
    return Stock();
}

Stock const
Building::buildCost( unsigned ) {
    return Stock();
}

