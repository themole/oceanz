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
    auto it = _wm->cityLayer()->cities().find( c );

    if( it == _wm->cityLayer()->cities().end() )
        return;

    Position cp = it->second;
    // find valid expansion fields

    std::list< Position > valid_list;

    for( auto it = c->positions().begin(); it != c->positions().end(); it ++ ) {
        std::list< Position > posl = it->allNeighbors();
        for( auto itp = posl.begin(); itp != posl.end(); itp++ ) {
            bool invalid = false;
            if( _wm->region( cp.x() + itp->x(), cp.y() + itp->y() ) == WATER )
                invalid = true;
            for( auto it2 = c->positions().begin(); it2 != c->positions().end(); it2 ++ )
                if( *it2 == *itp )
                    invalid = true;
            if( !invalid )
                valid_list.push_back( *it );
        }
    }

    valid_list.unique();


}
