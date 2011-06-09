#include "citycontrol.hh"

CityControl::CityControl( WorldMap * wm )
    : _wm( wm ) {
}

CityControl::~CityControl() {
}

void
CityControl::setWorldMap( WorldMap * wm ) {
    _wm = wm;
}

void
CityControl::buildCity( Position const & p, std::string const & name ) {
    name == name; p == p;
}

void
CityControl::upgradeCity( City * c ) {
    c = c;
}
