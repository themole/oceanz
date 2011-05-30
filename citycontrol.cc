#include "citycontrol.hh"

CityControl::CityControl( CityLayer & cl, RegionLayer const & rl )
    : _cl( cl ), _rl( rl ) {
}

CityControl::~CityControl() {
}

void
CityControl::buildCity( Position const & p, std::string const & name ) {
        _cl( p, new City( name ) );
}

void
CityControl::upgradeCity( Position const & p ) {
    p == p;
}
