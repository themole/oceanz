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
CityControl::upgradeCity( City::city_id id ) {
    if( !_wm ) return;

    City *c = _wm->cityLayer()->city( id );

    if( !c ) return;

    auto it = --c->localTiles().end();
    if( it == c->localTiles().end() )
        return;

    // get all neighbors of city
}
