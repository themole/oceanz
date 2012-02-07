#ifndef PATH_FINDER_HH
#define PATH_FINDER_HH

#include "worldmap.hh"
#include "position.hh"
#include "path.hh"

#include <queue>
#include <vector>
#include <set>
#include <map>
#include <list>

class PathFinder {

public:

    enum error_code {
        PATH_FOUND = 0,
        NO_PATH_FOUND = 1,
        NOT_RUN_YET = 2
    };

    // a position and the cost to get there
    typedef std::pair< Position, int > node;

    // comparison class to use with priority_queue
    struct Comp { bool operator()( node const & a, node const & b ); };

    typedef std::list< node > open_list;
    typedef std::set< Position > closed_list;

    static Path findPath( Position const & start,
                          Position const & dest,
                          WorldMap & map );

    static error_code error();

private:

    static error_code _error;

    static Position _start;
    static Position _dest;

    static Path _path;

    static open_list _olist;
    static closed_list _clist;

    // key = position, value = predeseccor
    static std::map< Position, Position > _pres;

    // puts all valid successors onto the open list
    static void expandNode( node const & n, WorldMap & map );
    // uses _pres to construc a Path object
    static Path constructPath();
};

#endif // PATH_FINDER_HH
