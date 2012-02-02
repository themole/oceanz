#include "pathfinder.hh"

Path
PathFinder::findPath( Position const & from,
                           Position const & to,
                           WorldMap const & map ) {

    _from = from;
    _to = to;

// setup open and closed list
    
    // clear open list
    _olist = open_list(); 

    // open list contains only starting node
    // starting from the end to then get path from beginning to end
    _olist.push( node( from.distanceTo( to ), 0, to ) );

    // clear closed list
    _clist.clear();

// A*
    bool valid_path_found = false;

    // current examinated node
    node cn;

    do {
        // get next node in queue
        cn = _olist.top();   
        // dequeue the node
        _olist.pop();

        if( cn.p == from ) {
            valid_path_found = true;
            break;
        }

        // put all successors on the open list
        expandNode( cn, map );

        // the current node now is completely examined
        _clist.push( cn );

    } while( !_olist.empty() )

    // if valid path was found from start to finish
    if( valid_path_found ) {
        #ifdef DEBUG
        std::err << "PathFinder: A* terminated. Valid Path found." << std::endl;
        #endif
        // TODO: create Path object containing the calculated path
        return Path();
    }

    // no valid path was found
    #ifdef DEBUG
    std::err << "PathFinder: A* terminated. No path found." << std::endl;
    #endif
    return Path();
}

void
PathFinder::expandNode( node const & n, WorldMap const & map ) {
    // find valid successors

}
