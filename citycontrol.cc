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

    CityLayer::city_info ci = _wm->cityLayer()->cityInfo( c->position() );


    auto it = c->localTiles().rbegin();
    if( it == c->localTiles().rend() )
        return;

    // level up city
    c->levelUp();

    std::cout << "making " << c->name() << " at ( " << c->position().x() << ", " << c->position().y() << " ) grow\t-> level " << c->level() << std::endl;

    // get all neighbors of city
    auto inRange = c->position().allInRange( it->distanceToNull() + 1 );

    std::set< Position > neighs;
    for( auto rit = inRange.begin(); rit != inRange.end(); rit++ ) {
        // if *rit is water globally ... go to next
        if( rit->x() < 0 || rit->y() < 0 || rit->x() >= _wm->sizeX() || rit->y() >= _wm->sizeY() )
            continue;
        if( _wm->regionLayer()->region( *rit )->is( WATER ) )
            continue;
        CityLayer::city_info ci = _wm->cityLayer()->cityInfo( *rit );
        // if no information about city ... go to next position
        auto ciit = ci.find( id );
        if( ciit == ci.end() )
            continue;
        else if( ciit->second != CityLayer::AROUND )
            continue;
        // current position is around city with city_id id
        neighs.insert( *rit );
    }
    // grow to exactly 2 positions
    
    while( neighs.size() > c->level() ) {
        auto it = neighs.begin();
        for( unsigned i = 0; i < rand() % neighs.size(); i++ )
            it++;
        neighs.erase( it );
    }
    for( auto nit = neighs.begin(); nit != neighs.end(); nit++ ) {
         c->addLocalTile( *nit );
         // put information into citylayer
         _wm->cityLayer()->setCityInfo( *nit, id, CityLayer::INSIDE );
    }
    checkAroundCity( c, it->distanceToNull() + 2 );
}

void
CityControl::checkAroundCity( City* c, unsigned range ) {
    auto all = c->position().allInRange( range );
    for( auto it = all.begin(); it != all.end(); it++ ) {
        // ceck if around city c
        auto neighs = it->allNeighbors();
        for( auto nit = neighs.begin(); nit != neighs.end(); nit++ ) {
            if( _wm->cityLayer()->insideCity( it->x(), it->y() ) != c->id() &&
                _wm->cityLayer()->insideCity( nit->x(), nit->y() ) == c->id() ) {
                _wm->cityLayer()->setCityInfo( *it, c->id(), CityLayer::AROUND );
                break;
            }
        }
    }
}
