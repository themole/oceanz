#include "citycontrol.hh"
#include <vector>

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

    if( c->maxLevel() ) return;

#ifdef DEBUG
    std::cout << "CityControl::upgradeCity( City::city_id id ): c->position() = " << c->position() << std::endl;
#endif
    CityLayer::city_info ci = _wm->cityLayer()->cityInfo( c->position() );


    auto it = c->localTiles().rbegin();
    if( it == c->localTiles().rend() )
        return;

    // level up city
    c->levelUp();

    std::cout << "making " << c->name() << " at ( " << c->position().x() << ", " << c->position().y() << " ) grow\t-> level " << c->level() << std::endl;

    // get all neighbors of city
    auto inRange = c->position().allInRange( it->distanceToNull() + 1 );

    std::vector< Position > neighs;
    for( auto rit = inRange.begin(); rit != inRange.end(); rit++ ) {
        // if *rit is water globally ... go to next
        if( rit->x() < 0 || rit->y() < 0 ||
            rit->x() >= _wm->sizeX() || rit->y() >= _wm->sizeY() )
            continue;
        if( _wm->regionLayer()->region( *rit )->is( WATER ) )
            continue;
        // analyze city info of currently examined position 
        CityLayer::city_info ci = _wm->cityLayer()->cityInfo( *rit );
        bool around_current = false;
        bool around_other = false;

        auto ciit = ci.find( c->id() );
        if( ciit == ci.end() ) continue;
        if( ciit->second == CityLayer::INSIDE ) continue;
        if( ciit->second == CityLayer::AROUND ) around_current = true;

        if( around_current )
            for( ciit = ci.begin(); ciit != ci.end(); ciit++ ) {
                if( ciit->first != c->id() && ciit->second == CityLayer::AROUND )
                    around_other = true;
            }

        // current position is around city with city_id id
        // not in any city and not around city with city_id not id
        if( around_current && !around_other )
            neighs.push_back( *rit );
    }

    if( neighs.size() == 0 ) {
        c->setMaxLevel( true );
        return;
    }

    int max_growth = rand() % 10 + 1;
    for( int j = 0; j < max_growth; j++ ) {
        // grow to random neighbors
        int i = rand() % neighs.size();
        // after growing to one neighbor place dummy pos( -1, -1 ) there
        // to indicate that growing there is no longer valid
//        if( /*already grown there*/ neighs[ i ] == Position( -1, -1 ) ) {
//            j--;
//            continue;
//        }
        c->addLocalTile( neighs[ i ] );
        _wm->cityLayer()->setCityInfo( neighs[ i ], id, CityLayer::INSIDE );
        neighs[ i ] = Position( -1, -1 );
    }
//    while( neighs.size() > rand() % 10 + 1 /*c->level()*/ ) {
//        auto it = neighs.begin();
//        for( unsigned i = 0; i < rand() % neighs.size(); i++ )
//            it++;
//        neighs.erase( it );
//    }
//    for( auto nit = neighs.begin(); nit != neighs.end(); nit++ ) {
//         c->addLocalTile( *nit );
//         // put information into citylayer
//         _wm->cityLayer()->setCityInfo( *nit, id, CityLayer::INSIDE );
//    }
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
