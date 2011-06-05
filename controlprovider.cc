#include "controlprovider.hh"

CityControl ControlProvider::_cc = CityControl( 0 );

CityControl const &
ControlProvider::cityControl() {
    return _cc;
}

void
ControlProvider::registerCityControl( CityControl & cc ) {
    _cc = cc;
}
