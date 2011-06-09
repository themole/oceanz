#include "regionlayer.hh"

#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <climits>


RegionLayer::RegionLayer( HeightLayer const & hmap ) 
    : Layer( hmap.sizeX(), hmap.sizeY() ),
      _ra( 0 ) {

    init( hmap );
}

RegionLayer::~RegionLayer() {
    uninit();
}

Region *
RegionLayer::region( int x, int y ) {
    if( x < 0 || y < 0 || x >= sizeX() || y >= sizeY() )
        return 0;
    return _ra[ index( x, y ) ];
}

Region *
RegionLayer::region( Position const & pos ) {
    return region( pos.x(), pos.y() );
}

RegionLayer::region_iterator 
RegionLayer::findRegion( unsigned id ) {
    for( auto it = _rs.begin(); it != _rs.end(); it++ ) {
        if( it->id() == id )
            return it;
    }
    return _rs.end();
}

// this is for setting region to ( x, y ) that already is in _rs
void
RegionLayer::setRegion( int x, int y, unsigned id ) {
    auto rit = findRegion( id );
    // if _rs does not contain that region ... do nothing
    if( rit == _rs.end() ) return;

    // now that the id is valid:

    // if there was a region set for ( x, y )
    // -> there is some stuff to do
    if( region( x, y ) != 0 ) {
        // if region at ( x, y ) already is the one to set
        // -> done
        if( *region( x, y ) == *rit ) return;
        // if not
        // -> reduce the size of that region
        region( x, y )->decrementSize();
        // now if the size is 0
        // -> remove the region from _rs, since it is no more
        // -> remove connections of any region to the 0 sized one
        if( region( x, y )->size() <= 0 ) {
            for( auto it = _rs.begin(); it != _rs.end(); it++ )
                it->unsetConnected( region( x, y ) );
            _rs.remove( *region( x, y ) );
        }
    }
    // now that everything is cleaned up
    // -> set new region to be at ( x, y )
    _ra[ index( x, y ) ] = &( *rit );
    
    // set up new connections between regions around
    auto plist = Position( x, y ).allNeighbors();
    for( auto it = plist.begin(); it != plist.end(); it++ ) {
        // others are connected to me
        Region* neighbor = region( *it );
        if( neighbor != 0 )
            neighbor->setConnected( region( x, y ) );
        // im connected to all others
        region( x, y )->setConnected( neighbor );
    }
}

void
RegionLayer::setNewRegion( int x, int y, region_type type ) {
    if( region( x, y ) != 0 ) {
        // if region at ( x, y ) already is the one to set
        // -> done
        if( region( x, y )->type() == type ) return;
        // if not
        // -> reduce the size of that region
        region( x, y )->decrementSize();
        // now if the size is 0
        // -> remove the region from _rs, since it is no more
        // -> remove connections of any region to the 0 sized one
        if( region( x, y )->size() <= 0 ) {
            for( auto it = _rs.begin(); it != _rs.end(); it++ )
                it->unsetConnected( region( x, y ) );
            _rs.remove( *region( x, y ) );
        }
    }

    _rs.push_back( Region( type ) );
    Region * rp = &_rs.back();
    _ra[ index( x, y ) ] = rp;


    // set up new connections between regions around
    auto plist = Position( x, y ).allNeighbors();
    for( auto it = plist.begin(); it != plist.end(); it++ ) {
        // others are connected to me
        Region* neighbor = region( *it );
        if( neighbor != 0 )
            neighbor->setConnected( region( x, y ) );
        // im connected to all others
        region( x, y )->setConnected( neighbor );
    }
}

void
RegionLayer::init( HeightLayer const & hmap ) {
    // assuming init is only called once
    _ra = new Region*[ size() ];
    for( int i = 0; i < size(); i++ )
        _ra[ i ] = 0;

    _rs.clear();
    
    // now extract region information off the given heightmap
    generateRegions( hmap );
}

void RegionLayer::uninit() {
    // assuming init was called
    delete[] _ra;
}

// consider a hex map layout like this
//         00  10  20  30  40 ... 
//       01  11  21  31  41
//     02  12  22  32  42 
//   03  13  23  33  43
// ...
// this is important for neighbor finding
// neighbors are numbered like this:
//    01  02
//  00  xy
void RegionLayer::generateRegions( HeightLayer const & hmap ) {
    // TODO: reimplement

// new pass 1 =====================00
    std::map< unsigned, std::set< unsigned > > region_eqs;

    for( int y = 0; y < sizeY(); y++ ) {
        for( int x = 0; x < sizeX(); x++ ) {
            // get the region type of current hex
            region_type xytype = heightToRegionType( hmap.height( x, y ) );
            
            // neighbor indeces
            int nx[3], ny[3];

            std::set< unsigned > equal_nbr_region_ids;
            nx[0] = x - 1, ny[0] = y;
            nx[1] = x - 1, ny[1] = y - 1;
            nx[2] = x    , ny[2] = y - 1;

            for( int i = 0; i < 3; i++ ) {
                if( nx[i] < 0 || ny[i] < 0 )
                    continue;
                Region const * nbr_region = region( nx[i], ny[i] );
                if( nbr_region == 0 )
                    continue;
                if( nbr_region->type() != xytype )
                    continue;
                else
                    equal_nbr_region_ids.insert( nbr_region->id() );
            }

            // if there is no neighbor with equal region type
            if( equal_nbr_region_ids.empty() )
                setNewRegion( x, y, xytype );
            else {
                setRegion( x, y, *equal_nbr_region_ids.begin() );
                // set regionequalities
                for( auto it = equal_nbr_region_ids.begin(); it != equal_nbr_region_ids.end();
                        it++ ) {
                    region_eqs[ *it ].insert( region( x, y )->id() );
                    region_eqs[ *it ].insert( equal_nbr_region_ids.begin(),
                                              equal_nbr_region_ids.end() );
                }
            }
            // always equal to self
            region_eqs[ region( x, y )->id() ].insert( region( x, y )->id() );
        }
    }

    for( auto it = region_eqs.begin(); it != region_eqs.end(); it++ ) {
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
            region_eqs[*it2].insert( it->second.begin(),
                                     it->second.end() );
    }

//    // print out group_equalities for debug
//    for( auto it = region_eqs.begin(); it != region_eqs.end(); it++ ) {
//        std::cout << "group " << it->first << " equals: ";
//        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
//            std::cout << *it2 << ", ";
//        std::cout << std::endl;
//    }

    for( int y = 0; y < sizeY(); y++ ) {
        for( int x = 0; x < sizeX(); x++ ) {
            setRegion( x, y, *region_eqs[ region( x, y )->id() ].begin() );
        }
    }

//    // print _rs
//    for( auto it = _rs.begin(); it != _rs.end(); it++ ) 
//        std::cout << std::endl << *it;
//    std::cout << std::endl;

    print();

    // now detecting coasts of both land and water regions
    for( auto it = _rs.begin(); it != _rs.end(); it++ ) {

        if( it->type() != WATER && it->type() != LAND )
            continue;

        Region coast( WATER_COAST );
        if( it->type() == LAND )
            coast.setType( LAND_COAST );
        _rs.push_back( coast );

        for( int y = 0; y < sizeY(); y++ ) {
            for( int x = 0; x < sizeX(); x++ ) {
                // if not in currently examined region
                if( region( x, y ) != &(*it) )
                    continue;

                auto plist = Position( x, y ).allNeighbors();
                for( auto pit = plist.begin(); pit != plist.end(); pit++ ) {
                    if( region( *pit ) == 0 ) continue;

                    switch( it->type() ) {
                    case WATER:
                        if( region( *pit )->type() == LAND ||
                            region( *pit )->type() == LAND_COAST )
                            setRegion( x, y, coast.id() );
                        break;
                    case LAND:
                        if( region( *pit )->type() == WATER ||
                            region( *pit )->type() == WATER_COAST )
                            setRegion( x, y, coast.id() );
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    print();
}

region_type RegionLayer::heightToRegionType( HeightLayer::height_type height ) const {
    if( height > 0 ) {
        return LAND;
    } else {
        return WATER;
    }
}

void RegionLayer::print() {
    for( int y = 0; y < _sy; y++ ) {
        std::cout << std::endl;
        for( int x = 0; x < _sx; x++ ) {
            if( x == 0 )
                for( int k = y + 2; k <= _sy; k++ )
                    std::cout << "  ";
            std::cout << std::setw( 3 ) << *region( x, y ) << "  ";
        }
    }
    std::cout << std::endl;
}
