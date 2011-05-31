#include "regionlayer.hh"

#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <climits>

RegionLayer::RegionLayer() :
    _sx( 0 ), _sy( 0 ), _r( 0 ) {
}

RegionLayer::RegionLayer( HeightLayer const & hmap ) :
    _sx( 0 ), _sy( 0 ), _r( 0 ) {

    init( hmap );
}

RegionLayer::~RegionLayer() {
    uninit();
}

int RegionLayer::sizeX() const {
    return _sx;
}

int RegionLayer::sizeY() const {
    return _sy;
}

unsigned RegionLayer::region( int x, int y ) const {
    return _r[( x % _sx ) + _sx * ( y % _sy )];
}

unsigned RegionLayer::region( Position const & pos ) const {
    return region( pos.x(), pos.y() );
}

void RegionLayer::setRegion( int x, int y, unsigned g, region_type t ) {

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
        std::cout
                << "Warining: in GroupMap::setGroup()\
            -> overwriting group type with different type"
                << std::endl;
        tp->second = t;
    }

    // set new region number
    _r[( x % _sx ) + _sx * ( y % _sy )] = g;

    // fix size of region
    sz = _s.find( region( x, y ) );
    if( sz == _s.end() )
        _s.insert( std::pair< unsigned, unsigned >( region( x, y ), 1 ) );
    else
        sz->second = sz->second + 1;
}

void RegionLayer::setRegion( int x, int y, unsigned g ) {
    // fix size of region that xy might already be in
    auto sz = _s.find( region( x, y ) );
    if( sz != _s.end() ) {
        if( sz->second != 0 )
            sz->second--;
        else
            _s.erase( sz );
    }

    // set new region number
    _r[( x % _sx ) + _sx * ( y % _sy )] = g;

    // fix size of region
    sz = _s.find( region( x, y ) );
    if( sz == _s.end() )
        _s.insert( std::pair< unsigned, unsigned >( region( x, y ), 1 ) );
    else
        sz->second = sz->second + 1;
}

unsigned RegionLayer::regionSize( unsigned group ) const {
    auto sz = _s.find( group );
    if( sz != _s.end() )
        return sz->second;
    else
        return 0;
}

unsigned RegionLayer::regionSizeX( unsigned r ) const {
    return regionMaxX( r ) - regionMinX( r );
}

unsigned RegionLayer::regionSizeY( unsigned r ) const {
    return regionMaxY( r ) - regionMinY( r );
}

int RegionLayer::regionMinX( unsigned r ) const {
    int min = INT_MAX;
    for( int x = 0; x < _sx; x++ )
        for( int y = 0; y < _sy; y++ ) {
            if( region( x, y ) == r && x < min )
                min = x;
        }
    return min;
}

int RegionLayer::regionMaxX( unsigned r ) const {
    int max = INT_MIN;
    for( int x = 0; x < _sx; x++ )
        for( int y = 0; y < _sy; y++ ) {
            if( region( x, y ) == r && x > max )
                max = x;
        }
    return max;
}

int RegionLayer::regionMinY( unsigned r ) const {
    int min = INT_MAX;
    for( int x = 0; x < _sx; x++ )
        for( int y = 0; y < _sy; y++ ) {
            if( region( x, y ) == r && y < min )
                min = y;
        }
    return min;
}

int RegionLayer::regionMaxY( unsigned r ) const {
    int max = INT_MIN;
    for( int x = 0; x < _sx; x++ )
        for( int y = 0; y < _sy; y++ ) {
            if( region( x, y ) == r && x > max )
                max = x;
        }
    return max;
}

region_type RegionLayer::regionType( unsigned group ) const {
    auto tp = _t.find( group );
    if( tp != _t.end() )
        return tp->second;
    else
        return NONE;
}

unsigned RegionLayer::greatestRegion( region_type type ) const {
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

unsigned RegionLayer::regionCount() const {
    return _s.size();
}

unsigned RegionLayer::regionCount( region_type type ) const {
    unsigned cnt = 0;
    for( auto it = _t.begin(); it != _t.end(); it++ )
        if( it->second == type )
            cnt++;
    return cnt;
}

bool RegionLayer::isNull() const {
    if( _sx == 0 || _sy == 0 || _r == 0 )
        return true;
    return false;
}

void RegionLayer::init( HeightLayer const & hmap ) {
    if( hmap.isNull() )
        return;
    _sx = hmap.sizeX();
    _sy = hmap.sizeY();

    if( _r == 0 ) {
        _r = new unsigned[_sx * _sy];
        for( int i = 0; i < _sx * _sy; i++ )
            _r[i] = (unsigned)-1;

        _t.clear(), _s.clear();

        generateRegions( hmap );
    }
}

void RegionLayer::uninit() {
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
void RegionLayer::generateRegions( HeightLayer const & hmap ) {
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
    for( auto it = region_equalities.begin(); it != region_equalities.end(); it++ ) {
        std::cout << "group " << it->first << " equals: ";
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ )
            std::cout << *it2 << ", ";
        std::cout << std::endl;
    }

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

    print();

    // step 4 ... clean up my maps
    // ===================================================== why in the world is once not enough
    for( auto it = _s.begin(); it != _s.end(); it++ )
        if( it->second == 0 ) {
            _s.erase( it );
            _t.erase( it->first );
        }
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
            switch( regionType( region( x, y ) ) ) {
            case WATER:         std::cout << "W"; break;
            case WATER_SHALLOW: std::cout << "w"; break;
            case WATER_MID:     std::cout << "W"; break;
            case WATER_DEEP:    std::cout << "D"; break;
            case LAND:          std::cout << "L"; break;
            case LAND_LOW:      std::cout << "l"; break;
            case LAND_MID:      std::cout << "L"; break;
            case LAND_HIGH:     std::cout << "H"; break;
            case COAST:         std::cout << "C"; break;
            case NONE:          std::cout << "N"; break;
            }
            std::cout << std::setw( 3 ) << region( x, y ) << "  ";
        }
    }
    std::cout << std::endl;
}
