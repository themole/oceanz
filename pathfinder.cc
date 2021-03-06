#include "pathfinder.hh"

#include <algorithm>

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
    return a.first.distanceTo( _start ) < b.first.distanceTo( _start );
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
    _olist.clear();
    _olist.push_front( node( _dest, 0 ) );

    // as long as the open list is not empty
    do {
        std::cout << "closed list:" << std::endl;
        if( _clist.empty() )
            std::cout << "\tempty" << std::endl;
        else
            for( auto cit = _clist.begin(); cit != _clist.end(); cit++ )
                std::cout << "\t" << *cit << std::endl;

        std::cout << "open list:" << std::endl;
        if( _olist.empty() )
            std::cout << "\tempty" << std::endl;
        else
            for( auto cit = _olist.begin(); cit != _olist.end(); cit++ )
                std::cout << "\t" << cit->first << std::endl;

        _olist.sort( PathFinder::Comp() );

        // get highest priority node
        node current = _olist.front();

        std::cout << "examining " << current.first << std::endl;
        
        // if path found return path
        if( current.first == _start ) {
            _error = PATH_FOUND;
            std::cout << "path found." << std::endl;
            return constructPath();
        }
        
        // if path not found yet expand the current node
        // i.e. put all successors onto the open list
        expandNode( current, map );
        
        // now the current node is completely examined
        _clist.insert( current.first );

        // remove from open list
        _olist.pop_front();
    } while( !_olist.empty() );

    _error = NO_PATH_FOUND;
    return _path = Path();
}

void
PathFinder::expandNode( PathFinder::node const & current, WorldMap & map )  {
    std::cout << "expanding " << current.first << std::endl;
    // get all neighbors of current position that
    // are in the same region
    auto neighs = current.first.allNeighborsIn( 0, map.sizeX(), 0, map.sizeY() );
    std::list< Position > valid_neighs;

    for( auto nit = neighs.begin(); nit != neighs.end(); nit++ ) {
        if( !( map.region( nit->x(), nit->y() )->id() != map.region( current.first )->id() ) ) {
            valid_neighs.push_back( *nit );
        }
    }

    std::cout << "\t" << valid_neighs.size() << " valid neighbors" << std::endl;
    
    // for all valid successors
    for( auto nit = valid_neighs.begin(); nit != valid_neighs.end(); nit++ ) {
        // if already on closed list, i.e. already completely examined
        // do nothing
        if( _clist.find( *nit ) != _clist.end() ) 
            continue;

        // put relation into _pres
        _pres[ *nit ] = current.first;

        // calculate costs to this position along current path
        int tentative_g = current.second +1;

        // find out if already on open list
        auto it = _olist.begin();
        for( ; it != _olist.end(); it++ )
            if( it->first == *nit ) break;

        int h = tentative_g + nit->distanceTo( _start );

        // put current successor on open list it not yet there
        // if on open list already just update h
        // -> h is current cost plus estimated cost to _start
        if( it != _olist.end() ) {
            std::cout << "\t" << *nit << " already on olist" << std::endl;
            if( it->second > h ) it->second = h;
        }
        else
            _olist.push_back( node( *nit, h ) );
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
