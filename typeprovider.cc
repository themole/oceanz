#include "typeprovider.hh"

GoodTypeList TypeProvider::_gtl = GoodTypeList();
ShipTypeList TypeProvider::_stl = ShipTypeList();

void
TypeProvider::loadGoodTypeList( GoodTypeListLoader const & gtll ) {
    gtll.load( TypeProvider::_gtl );
}

void
TypeProvider::loadShipTypeList( ShipTypeListLoader const & stll ) {
    stll.load( TypeProvider::_stl );
}

GoodType const &
TypeProvider::goodType( std::string const & name ) {
    return _gtl.get( name );
}

ShipType const &
TypeProvider::shipType( std::string const & name ) {
    return _stl.get( name );
}
