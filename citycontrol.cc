#include "citycontrol.hh"

CityControl::CityControl( CityLayer & cl, RegionLayer const & rl )
    : _cl( cl ), _rl( rl ) {
}

CityControl::~CityControl() {
}

void
CityControl::buildCity( Position const & p, std::string const & name ) {
    name == name; p == p;
}

void
CityControl::upgradeCity( Position const & p ) {
    p == p;
}
