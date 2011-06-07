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
RegionLayer::region( int x, int y ) const {
    return _ra[( x % _sx ) + _sx * ( y % _sy )];
}

Region *
RegionLayer::region( Position const & pos ) const {
    return region( pos.x(), pos.y() );
}

Region *
RegionLayer::regionByID( unsigned id ) const {
    for( auto it = _rs.begin(); it != _rs.end(); it++ ) {
        if( (*it)->id() == id )
            return *it;
    }
    return 0;
}

// known issues:
//  - if you put a new region on a hex that is the only one
//    holding together thw parts of a region ... there is no
//    way to tell that these region now are 2 distinct once
//    they will continue to be exactly 1 region ... but not connected -> buggy
void
RegionLayer::setRegion( int x, int y, Region * r ) {

// list of all fields surrounding ( x, y )
    std::list< Position > plist = Position( x, y ).allNeighbors();
 
// FIX SIZE AND LINKS OF A REGION THAT MIGHT HAVE BEEN HERE

    if( region( x, y ) != 0 ) {
        region( x, y )->decrementSize();

        // if this was last hex of a region take it out of the set
        // fix all connections of surrounding regions
        // and free heap space
        if( region( x, y )->size() <= 0 ) {
            // go through all regions that mean to be connected
            // and unset
            for( auto it  = region( x, y )->connected().begin();
                      it != region( x, y )->connected().end();
                      it++ ) {
                (*it)->unsetConnected( region( x, y ) );
            }
            // erase region( x, y ) from _rs
            // => do not track that region anymore

    // print _rs
    for( auto it = _rs.begin(); it != _rs.end(); it++ ) 
        std::cout << std::endl << *(*it);
    std::cout << std::endl;

    print();

            _rs.erase( region( x, y ) );
            // delete region
            delete region( x, y );
        }
    }

    // set Region link in hex array
    _ra[( x % _sx ) + _sx * ( y % _sy )] = r;

    // increase size of region ( since it now occupies one more hex )
    // ... btw ... region( x, y ) returns the new region now
    region( x, y )->incrementSize();

    // insert to set of tracked regions
    //  => will not be added if already in
    _rs.insert( region( x, y ) );

    // setup new connections between regions
    for( auto it = plist.begin(); it != plist.end(); it++ ) {
        if( it->x() < 0 || it->y() < 0 )
            continue;
        if( region( *it ) == 0 )
            continue;
        if( region( *it ) == region( x, y ) )
            continue;

        // set up connection in both directions
        region( x, y )->setConnected( region( *it ) );
        region( *it )->setConnected( region( x, y ) ); 
    }
    // done
}

Region *
RegionLayer::greatestRegion( region_type type ) const {
    Region * max = *_rs.begin();
    for( auto it = _rs.begin(); it != _rs.end(); it++ ) {
        if( (*it)->size() > max->size() && (*it)->type() == type )
            max = *it;
    }
    return max;
}

unsigned
RegionLayer::regionCount() const {
    return _rs.size();
}

unsigned
RegionLayer::regionCount( region_type type ) const {
    unsigned cnt = 0;
    for( auto it = _rs.begin(); it != _rs.end(); it++ )
        if( (*it)->type() == type )
            cnt++;
    return cnt; 
}

void
RegionLayer::init( HeightLayer const & hmap ) {
    // if _ra initialized ... delete it
    if( _ra != 0 ) 
        delete[] _ra;

    // create new array
    _ra = new Region*[ size() ];

    // if already regions in set of regions
    // delete all region objects
    if( !_rs.empty() )
        for( auto it = _rs.begin(); it != _rs.end(); it++ ) 
            if( *it != 0 )
                delete *it;

    // just in case always clear the set of region pointers
    _rs.clear();

    // initialize the array to null pointers
    for( int i = 0; i < size(); i++ )
        _ra[ i ] = (Region*) 0;

    // now extract region information off the given heightmap
    generateRegions( hmap );
}

void RegionLayer::uninit() {
    if( _ra != 0 )
        delete[] _ra;

    if( !_rs.empty() )
        for( auto it = _rs.begin(); it != _rs.end(); it++ ) 
            if( *it != 0 )
                delete *it;
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
                setRegion( x, y, new Region( xytype ) );
            else {
                setRegion( x, y, regionByID( *equal_nbr_region_ids.begin() ) );
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

    // print out group_equalities for debug
    for( auto it = region_eqs.begin(); it != region_eqs.end(); it++ ) {
        std::cout << "group " << it->first << " equals: ";
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
            std::cout << *it2 << ", ";
        std::cout << std::endl;
    }

    for( int y = 0; y < sizeY(); y++ ) {
        for( int x = 0; x < sizeX(); x++ ) {
            setRegion( x, y, regionByID( *region_eqs[ region( x, y )->id() ].begin() ) );
        }
    }

    // print _rs
    for( auto it = _rs.begin(); it != _rs.end(); it++ ) 
        std::cout << std::endl << *(*it);
    std::cout << std::endl;

    print();


// new pass 1 end =================00

/* old cca ----------------------------------------------------------------------------
    // pass 1 ... get some temporary regions going
    // current region number
    unsigned n = 0;
    // for each region stores the smallest region number found that it is equal to
    std::map< unsigned, std::set< unsigned > > region_equalities;

    for( int y = 0; y < _sy; y++ ) {
        for( int x = 0; x < _sx; x++ ) {

            // current region type
            region_type txy = heightToRegionType( hmap.height( x, y ) );

            // neighbor indeces
            int nx[3];
            int ny[3];

            // name sais it
            std::set< unsigned > equal_neighbor_regions;

            nx[0] = x - 1, ny[0] = y;
            nx[1] = x - 1, ny[1] = y - 1;
            nx[2] = x, ny[2] = y - 1;

            for( int i = 0; i < 3; i++ ) {
                if( nx[i] == -1 || ny[i] == -1 )
                    continue;
                if( regionType( region( nx[i], ny[i] ) ) != txy )
                    continue;
                else
                    equal_neighbor_regions.insert( region( nx[i], ny[i] ) );
            }

            if( equal_neighbor_regions.empty() )
                setRegion( x, y, n++, txy );
            else {
                setRegion( x, y, *equal_neighbor_regions.begin() );
                for( auto it = equal_neighbor_regions.begin(); it
                        != equal_neighbor_regions.end(); it++ ) {
                    region_equalities[*it].insert( region( x, y ) );
                    region_equalities[*it].insert(
                                                   equal_neighbor_regions.begin(),
                                                   equal_neighbor_regions.end() );
                }
            }
            region_equalities[region( x, y )].insert( region( x, y ) );
        }
    }

    for( auto it = region_equalities.begin(); it != region_equalities.end(); it++ ) {
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
            region_equalities[*it2].insert( it->second.begin(),
                                            it->second.end() );
    }

    // print out group_equalities for debug
//    for( auto it = region_equalities.begin(); it != region_equalities.end(); it++ ) {
//        std::cout << "group " << it->first << " equals: ";
//        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
//            std::cout << *it2 << ", ";
//        std::cout << std::endl;
//    }

    // second pass ... give all equivalent groups
    // the smallest number of that equivilance class
    for( int y = 0; y < _sy; y++ ) {
        for( int x = 0; x < _sx; x++ ) {
            setRegion( x, y, *region_equalities[region( x, y )].begin() );
        }
    }

    // third step ... calculate COAST groups ... coasts of the same water region
    // get the same number
    for( auto it = _t.begin(); it != _t.end(); it++ ) {
        // for all water groups
        if( it->second == WATER ) {
            // get next free region number
            n++;
            // find all neighbors that are LAND and assign it to one region
            for( int y = 0; y < _sy; y++ ) {
                for( int x = 0; x < _sx; x++ ) {
                    // if not in the current looked at region
                    if( region( x, y ) != it->first )
                        continue;
                    // indeces of all 6 neighbors
                    int nx[6];
                    int ny[6];
                    nx[0] = x - 1, ny[0] = y;       // left
                    nx[1] = x - 1, ny[1] = y - 1;   // top left
                    nx[2] = x    , ny[2] = y - 1;   // top right
                    nx[3] = x + 1, ny[3] = y;       // right
                    nx[4] = x + 1, ny[4] = y + 1;   // bottom right
                    nx[5] = x    , ny[5] = y + 1;   // bottom left
                    for( int i = 0; i < 6; i++ ) {
                        // invalid neighbors
                        if( nx[i] == -1 || ny[i] == -1 || nx[i] == _sx || ny[i]
                                == _sy )
                            continue;
                        if( regionType( region( nx[i], ny[i] ) ) == LAND )
                            setRegion( nx[i], ny[i], n, COAST );
                    }
                }
            }
        }
        n++;
    }

//   print();

    // step 4 ... clean up my maps
    // ===================================================== why in the world is once not enough
    for( auto it = _s.begin(); it != _s.end(); it++ )
        if( it->second == 0 ) {
            _s.erase( it );
            _t.erase( it->first );
        }

    // for debugging
//    for( auto it = _t.begin(); it != _t.end(); it++ )
//        std::cout << "region " << it->first << " type: " << it->second << " size: " << _s[it->first] << std::endl;

    */ // old cca end ---------------------
}

region_type RegionLayer::heightToRegionType( HeightLayer::height_type height ) const {
    if( height > 0 ) {
        return LAND;
    } else {
        return WATER;
    }
}

void RegionLayer::print() const {
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
