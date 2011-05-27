#include "regionmap.hh"

#include <iostream>
#include <iomanip>
#include <map>
#include <set>

RegionMap::RegionMap()
    : _sx( 0 ), _sy( 0 ), _r( 0 ) {
}

RegionMap::RegionMap( HeightMap const & hmap )
    : _sx( 0 ), _sy( 0 ), _r( 0 ) {

    init( hmap );
}

RegionMap::~RegionMap() {
    uninit();
}

int
RegionMap::sizeX() const {
    return _sx;
}

int
RegionMap::sizeY() const {
    return _sy;
}

unsigned
RegionMap::region( int x, int y ) const {
    return _r[ ( x%_sx ) + _sx * ( y%_sy ) ];
}

unsigned
RegionMap::region( Position const & pos ) const {
    return region( pos.x(), pos.y() );
}

void
RegionMap::setRegion( int x, int y,
                    unsigned g, region_type t) {

    // fix size of region that xy might already be in
    auto sz = _s.find( region( x, y ) );
    if( sz != _s.end() ) {
        if( sz->second != 0 )
            sz->second--;
        else
            _s.erase( sz );
    }

    // set type of region number
    // if already set ... do not set the region!!!!
    auto tp = _t.find( g );
    if( tp == _t.end() )
        _t.insert( std::pair< unsigned, region_type >( g, t ) );
    else if( tp->second != t ) {
        std::cout << "Warining: in GroupMap::setGroup()\
            -> overwriting group type with different type" << std::endl;
        tp->second = t;
    }


    // set new region number
    _r[ ( x%_sx ) + _sx * ( y%_sy ) ] = g;

    // fix size of region
    sz = _s.find( region( x, y ) );
    if( sz == _s.end() )
        _s.insert( std::pair< unsigned, unsigned >( region( x, y ), 1 ) );
    else
        sz->second = sz->second + 1;
}

void
RegionMap::setRegion( int x, int y, unsigned  g ) {
    // fix size of region that xy might already be in
    auto sz = _s.find( region( x, y ) );
    if( sz != _s.end() ) {
        if( sz->second != 0 )
            sz->second--;
        else
            _s.erase( sz );
    }

    // set new region number
    _r[ ( x%_sx ) + _sx * ( y%_sy ) ] = g;

    // fix size of region
    sz = _s.find( region( x, y ) );
    if( sz == _s.end() )
        _s.insert( std::pair< unsigned, unsigned >( region( x, y ), 1 ) );
    else
        sz->second = sz->second + 1;
}
    

unsigned
RegionMap::regionSize( unsigned group ) const {
    auto sz = _s.find( group );
    if( sz != _s.end() )
        return sz->second;
    else
        return 0;
}

RegionMap::region_type
RegionMap::regionType( unsigned group ) const {
    auto tp = _t.find( group );
    if( tp != _t.end() )
        return tp->second;
    else
        return NONE;
}

unsigned
RegionMap::greatestRegion( region_type type ) const {
    unsigned max = 0;
    unsigned max_g = 0;
    for( auto it = _s.begin(); it != _s.end(); it++ ) 
        if( max < it->second && regionType( it->first ) == type ) {
            // i want the region number
            max = it->second;
            max_g = it->first;
        }
    return max_g;
}

unsigned
RegionMap::regionCount() const {
    return _s.size();
}

unsigned 
RegionMap::groupCount( region_type type ) const {
    unsigned cnt = 0;
    for( auto it = _t.begin(); it != _t.end(); it++ )
        if( it->second == type )
            cnt++;
    return cnt;
}

bool
RegionMap::isNull() const {
    if( _sx == 0 || _sy == 0 || _r == 0 )
        return true;
    return false;
}

void
RegionMap::init( HeightMap const & hmap ) {
    if( hmap.isNull() )
        return;
    _sx = hmap.sizeX();
    _sy = hmap.sizeY();

    if( _r == 0 ) {
        _r = new unsigned[ _sx * _sy ];
        for( int i = 0; i < _sx * _sy; i++ )
            _r[ i ] = (unsigned) -1;

        _t.clear(), _s.clear();

        connected_component_analasys( hmap );
    }
}

void
RegionMap::uninit() {
    if( _r != 0 )
       delete[] _r;
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
void
RegionMap::connected_component_analasys( HeightMap const & hmap ) {
  // pass 1 ... get some temporary groups going
    // current region number
    unsigned n = 0;
    // for each region stores the smallest region number found that it is equal to
    std::map< unsigned, std::set< unsigned > > group_equalities;

    for( int y = 0; y < _sy; y++ ) {
        for( int x = 0; x < _sx; x++ ) {

            // current region type
            region_type txy = heightToRegionType( hmap.height( x, y ) );

            // neighbor indeces
            int nx[3]; int ny[3];

            // name sais it
            std::set< unsigned > equal_neighbor_groups;

            nx[0] = x-1, ny[0] = y;
            nx[1] = x-1, ny[1] = y-1;
            nx[2] = x  , ny[2] = y-1;
            
            for( int i = 0; i < 3; i++ ) {
                if( nx[i] == -1 || ny[i] == -1 )
                    continue;
                if( regionType( region( nx[i], ny[i] ) ) != txy )
                    continue;
                else 
                    equal_neighbor_groups.insert( region( nx[i], ny[i] ) );
            }

            if( equal_neighbor_groups.empty() )
                setRegion( x, y, n++, txy );
            else {
                setRegion( x, y, *equal_neighbor_groups.begin() );
                for( auto it = equal_neighbor_groups.begin();
                        it != equal_neighbor_groups.end();
                        it++ ) {
                    group_equalities[ *it ].insert( region( x, y ) );
                    group_equalities[ *it ].insert( equal_neighbor_groups.begin(),
                                                    equal_neighbor_groups.end() );
                }
            }
            group_equalities[ region( x, y ) ].insert( region( x, y ) );
        }
    }

    for( auto it = group_equalities.begin(); it != group_equalities.end(); it++ ) {
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
            group_equalities[ *it2 ].insert( it->second.begin(), it->second.end() );
    }



    // print out group_equalities for debug
    for( auto it = group_equalities.begin(); it != group_equalities.end(); it++ ) {
        std::cout << "group " << it->first << " equals: ";
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
            std::cout << *it2 << ", ";
        std::cout << std::endl;
    }

  // second pass ... give all equivalent groups
  // the smallest number of that equivilance class
    for( int y = 0; y < _sy; y++ ) {
        for( int x = 0; x < _sx; x++ ) {
            setRegion( x, y, *group_equalities[ region( x, y ) ].begin() );
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
                    int nx[6]; int ny[6];
                     nx[0] = x-1, ny[0] = y;    // left
                     nx[1] = x-1, ny[1] = y-1;  // top left
                     nx[2] = x  , ny[2] = y-1;  // top right
                     nx[3] = x+1, ny[3] = y;    // right
                     nx[4] = x+1, ny[4] = y+1;  // bottom right
                     nx[5] = x  , ny[5] = y+1;  // bottom left
                    for( int i = 0; i < 6; i++ ) {
                        // invalid neighbors
                        if( nx[i] == -1 || ny[i] == -1 || nx[i] == _sx || ny[i] == _sy )
                            continue;
                        if( regionType( region( nx[i], ny[i] ) ) == LAND )
                            setRegion( nx[i], ny[i], n, COAST );
                    }
                }
            }
        }
        n++;
    }

    print();

  // step 4 ... clean up my maps
    // ===================================================== why in the world is once not enough
    for( auto it = _s.begin(); it != _s.end(); it++ )
        if( it->second == 0 ) {
            _s.erase( it );
            _t.erase( it->first );
        }
}

RegionMap::region_type
RegionMap::heightToRegionType( short height ) const {
    if( height > 0 )
        return LAND;
    else
        return WATER;
}

void
RegionMap::print() const {
    for( int y = 0; y < _sy; y++ ) {
        std::cout << std::endl;
        for( int x = 0; x < _sx; x++ ) {
            if( x == 0 )
                for( int k = y+2; k <= _sy; k++ )
                    std::cout << "  ";
            switch( regionType( region( x, y ) ) ) {
                case WATER: std::cout << "W"; break;
                case  LAND: std::cout << "L"; break;
                case COAST: std::cout << "C"; break;
                case  NONE: std::cout << "N"; break;
            }
            std::cout <<  std::setw(3) <<  region( x, y ) << "  ";
        }
    }
    std::cout << std::endl;
}
