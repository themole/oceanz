#include "pathfinder.hh"

// static initialization
PathFinder::error_code PathFinder::_error = PathFinder::NOT_RUN_YET;
Position PathFinder::_start;
Position PathFinder::_dest;
Path PathFinder::_path;
PathFinder::open_list PathFinder::_olist;
PathFinder::closed_list PathFinder::_clist;
std::map< Position, Position > PathFinder::_pres;

// returns true if a is closer to PathFinder::_dest than b
// if PathFinder::destination is not set behavior is undefined
bool PathFinder::Comp::operator()( PathFinder::node const & a, PathFinder::node const & b ) {
    return a.first.distanceTo( _start ) > b.first.distanceTo( _start );
}

// uses a-star algorithm -> search from dest to start
Path
PathFinder::findPath( Position const & start,
                      Position const & dest,
                      WorldMap & map ) {

    _start = start;
    _dest = dest;

    _path.clear();
    _pres.clear();

  // setup open and closed list
    // closed list is empty in the beginning
    _clist.clear();
    // open list only containes dest in the beginning
    while( !_olist.empty() )
        _olist.pop();
    _olist.push( node( _dest, 0 ) );

    // as long as the open list is not empty
    do {
        // get highest priority node
        node current = _olist.top();
        _olist.pop();
        
        // if path found return path
        if( current.first == _start ) {
            _error = PATH_FOUND;
            return constructPath();
        }
        
        // if path not found yet expand the current node
        // i.e. put all successors onto the open list
        expandNode( current, map );
        
        // now the current node is completely examined
        _clist.insert( current.first );
    } while( !_olist.empty() );

    _error = NO_PATH_FOUND;
    return _path = Path();
}

void
PathFinder::expandNode( PathFinder::node const & current, WorldMap & map )  {
    // get all neighbors of current position that
    // are in the same region
    auto neighs = current.first.allNeighborsIn( 0, map.sizeX(), 0, map.sizeY() );

    for( auto nit = neighs.begin(); nit != neighs.end(); nit++ ) {
        if( map.region( nit->x(), nit->y() )->id() != map.region( current.first )->id() ) {
            neighs.erase( nit );
            nit = neighs.begin();
        }
    }
    
    // for all valid successors
    for( auto nit = neighs.begin(); nit != neighs.end(); nit++ ) {
        // if already on closed list, i.e. already completely examined
        // do nothing
        if( _clist.find( *nit ) != _clist.end() )
            continue;

        // put relation inte _pres
        _pres[ *nit ] = current.first;

        // calculate costs to this position along current path
        int tentative_g = current.second +1;
        // put current successor on open list
        // -> h is current cost plus estimated cost to _start
        _olist.push( node( *nit, tentative_g + nit->distanceTo( _start ) ) );
    }
}

Path
PathFinder::constructPath() {
    if( error() ) {
#ifdef DEBUG
        std::cerr << "path not constructable ... " << ( (PathFinder::error() == NOT_RUN_YET) ? "pathfinder not run yet" : "no path found" ) << std::endl;
#endif
        return Path();
    }
    Path ret = Path();
    Position it = _start;
    ret.add( _start );
    while( it != _dest ) {
        ret.add( _pres[ it ] );
        it = _pres[ it ];
    }
    return ret;
}

PathFinder::error_code
PathFinder::error() {
    return _error;
}
