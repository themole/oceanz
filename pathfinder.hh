#ifndef PATH_FINDER_HH
#define PATH_FINDER_HH

#include "worldmap.hh"
#include "position.hh"
#include "path.hh"

#include <priority_queue>
#include <list>

class PathFinder {

public:

    // represent a node used by a*
    struct node {
        // f is distance to goal
        // g is length of currently known shortest path to here
        int f, g;
        Position p;
        node* prev;

        node( int ff, int gg, Position pp ) {
           f = ff, g = gg, p = pp;
           prev = 0;
        }

        int cost() {
            return f + g;
        }

        // comparison parameter is f ... distance to goal
        bool operator<( node const & rhs ) {
            return f < rhs.f;
        }

        bool operator>( node const & rhs ) {
            return f > rhs.f; 
        }
    };

    // compares position a and b by distance to _from
    // returns true if a.distanceTo( _from ) < b.distanceTo( _from )
    // in any other case returns false
    // used to provide comparison function for a priority_queue
    static bool comp( Position const & a, Position const & b );

    // returns the shortest path from 'from' to 'to' on 'map'
    // uses A*-algorithm
    static Path findPath( Position const & from, Position const & to, WorldMap const & map );

    // to not write so much
    typedef priority_queue< node > open_list;
    typedef list< node > closed_list;

private:
    // checks all neighbors in the same region and
    // puts them into the open list if either
    // - it was found the first time or
    // - a better way to that neighbor was found
    static void expandNode( node const & n, WorldMap const & map );

private:

    static node _from;
    static node _to;

    static open_list    _olist;
    static closed_list  _clist;

    // for reference
    static Path _last;

};

#endif // PATH_FINDER_HH
