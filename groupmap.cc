#include "groupmap.hh"

#include <iostream>
#include <iomanip>
#include <map>
#include <set>

GroupMap::GroupMap()
    : _sx( 0 ), _sy( 0 ), _g( 0 ) {
}

GroupMap::GroupMap( HeightMap< short > const & hmap ) {
    init( hmap );
}

GroupMap::~GroupMap() {
    uninit();
}

int
GroupMap::sizeX() const {
    return _sx;
}

int
GroupMap::sizeY() const {
    return _sy;
}

unsigned
GroupMap::group( int x, int y ) const {
    return _g[ ( x%_sx ) + _sx * ( y%_sy ) ];
}

unsigned
GroupMap::group( Position const & pos ) const {
    return group( pos.x(), pos.y() );
}

void
GroupMap::setGroup( int x, int y,
                    unsigned g, GroupType t) {

    // fix size of group that xy might already be in
    auto sz = _s.find( group( x, y ) );
    if( sz != _s.end() ) {
        if( sz->second != 0 )
            sz->second--;
        else
            _s.erase( sz );
    }

    // set type of group number
    // if already set ... do not set the group!!!!
    auto tp = _t.find( g );
    if( tp == _t.end() )
        _t.insert( std::pair< unsigned, GroupType >( g, t ) );
    else if( tp->second != t ) {
        std::cout << "Warining: in GroupMap::setGroup()\
            -> overwriting group type with different type" << std::endl;
        tp->second = t;
    }


    // set new group number
    _g[ ( x%_sx ) + _sx * ( y%_sy ) ] = g;

    // fix size of group
    sz = _s.find( group( x, y ) );
    if( sz == _s.end() )
        _s.insert( std::pair< unsigned, unsigned >( group( x, y ), 1 ) );
    else
        sz->second = sz->second + 1;
}

unsigned
GroupMap::groupSize( unsigned group ) const {
    auto sz = _s.find( group );
    if( sz != _s.end() )
        return sz->second;
    else
        return 0;
}

GroupMap::GroupType
GroupMap::groupType( unsigned group ) const {
    auto tp = _t.find( group );
    if( tp != _t.end() )
        return tp->second;
    else
        return NONE;
}

unsigned
GroupMap::greatestGroup( GroupType type ) const {
    unsigned max = 0;
    unsigned max_g = 0;
    for( auto it = _s.begin(); it != _s.end(); it++ ) 
        if( max < it->second && groupType( it->first ) == type ) {
            // i want the group number
            max = it->second;
            max_g = it->first;
        }
    return max_g;
}

unsigned
GroupMap::groupCount() const {
    return _s.size();
}

unsigned 
GroupMap::groupCount( GroupType type ) const {
    unsigned cnt = 0;
    for( auto it = _t.begin(); it != _t.end(); it++ )
        if( it->second == type )
            cnt++;
    return cnt;
}

bool
GroupMap::isNull() const {
    if( _sx == 0 || _sy == 0 || _g == 0 )
        return true;
    return false;
}

void
GroupMap::init( HeightMap< short > const & hmap ) {
    if( hmap.isNull() )
        return;
    _sx = hmap.sizeX();
    _sy = hmap.sizeY();

    _g = new unsigned[ _sx * _sy ];
    for( int i = 0; i < _sx * _sy; i++ )
        _g[ i ] = (unsigned) -1;

    _t.clear(), _s.clear();

    connected_component_analasys( hmap );
}

void
GroupMap::uninit() {
   if( !isNull() )
       delete[] _g;
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
GroupMap::connected_component_analasys( HeightMap< short > const & hmap ) {
  // pass 1 ... get some temporary groups going
    // current group number
    unsigned n = 0;
    // for each group stores the smallest group number found that it is equal to
    std::map< unsigned, unsigned > group_equalities;

    for( int y = 0; y < _sy; y++ ) {
        for( int x = 0; x < _sx; x++ ) {

            // current group type
            GroupType txy = heightToType( hmap.height( x, y ) );

            // neighbor indeces
            int nx[3]; int ny[3];

            // name sais it
            std::set< unsigned > groups_of_neighbors_with_same_type;

            nx[0] = x-1, ny[0] = y;
            nx[1] = x-1, ny[1] = y-1;
            nx[2] = x  , ny[2] = y-1;

            // fill groups_of_neighbors_with_same_type
            for( int i = 0; i < 3; i++ )
                // invalid neighbor
                if( nx[i] == -1 || ny[i] == -1 )
                    continue;
                // if type matches -> instert to groups_of_neighbors_with_same_type
                else if( heightToType( hmap.height( nx[i], ny[i] ) ) == txy ) {
                    groups_of_neighbors_with_same_type.insert( group( nx[i], ny[i] ) );
                }

            // decide wich group number i get
            if( groups_of_neighbors_with_same_type.empty() ) {
                // no neighbors of same type
                setGroup( x, y, n, txy );
                group_equalities[ n ] = n++;
                if( n == 11 ) n++;
            } else {
                // some number of neighbors with same type
                // ill take the smalles group number of equal neighbors
                setGroup( x, y, *groups_of_neighbors_with_same_type.begin(), txy );
                // update group_equalities
                for( auto it = ++groups_of_neighbors_with_same_type.begin();
                        it != groups_of_neighbors_with_same_type.end();
                        it++ ) {
                    // if a neighbors group is set to be equal to group with higher
                    // group number than mine -> set it to mine
                    if( group_equalities[ *it ] >= group( x, y ) )
                        group_equalities[ *it ] = group( x, y );
                }
            }
        }
    }
    print();

    // print out group_equalities for debug
    for( auto it = group_equalities.begin(); it != group_equalities.end(); it++ ) {
        std::cout << "group " << it->first << " = group " << it->second << "\t";
    } std::cout << std::endl;

  // second pass ... give all equivalent groups
  // the smallest number of that equivilance class
    for( int y = 0; y < _sy; y++ ) {
        for( int x = 0; x < _sx; x++ ) {
            // current group
            unsigned grp = group( x, y );
            // as long as there is a smaller group number of the same class
            while( grp > group_equalities[ grp ] )
                // take on that number
                grp = group_equalities[ grp ];
            // update group number
            setGroup( x, y, grp, groupType( grp ) );
        }
    }

  // third step ... calculate COAST groups ... coasts of the same water group
  // get the same number
    for( auto it = _t.begin(); it != _t.end(); it++ ) {
        // for all water groups
        if( it->second == WATER ) {
            // get next free group number
            n++;
            // find all neighbors that are LAND and assign it to one group
            for( int y = 0; y < _sy; y++ ) {
                for( int x = 0; x < _sx; x++ ) {
                    // if not in the current looked at group
                    if( group( x, y ) != it->first )
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
                        if( groupType( group( nx[i], ny[i] ) ) == LAND )
                            setGroup( nx[i], ny[i], n, COAST );
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

GroupMap::GroupType
GroupMap::heightToType( short height ) const {
    if( height > 0 )
        return LAND;
    else
        return WATER;
}

void
GroupMap::print() const {
    for( int y = 0; y < _sy; y++ ) {
        std::cout << std::endl;
        for( int x = 0; x < _sx; x++ ) {
            if( x == 0 )
                for( int k = y; k < _sx; k++ )
                    std::cout << "  ";
            switch( groupType( group( x, y ) ) ) {
                case WATER: std::cout << "W"; break;
                case  LAND: std::cout << "L"; break;
                case COAST: std::cout << "C"; break;
                case  NONE: std::cout << "N"; break;
            }
            std::cout <<  std::setw(3) <<  group( x, y ) << "  ";
        }
    }
    std::cout << std::endl;
}
