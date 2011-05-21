#ifndef HEX_MAP_HH
#define HEX_MAP_HH

#include "tile.hh"

// represents a hex grid based map with following layout
//          00  10  20  30  40 ...> x-Axis
//        01  11  21  31  41 ... 
//      02  12  22  32  42 ...
//   ..  ..  ..  ..  ..  ...
//   / y-Axis

#include <ostream>

class HexMap {

public:
    // creates a "null" object
    HexMap();
    // creates width*height sized map
    HexMap( int width, int height );
    // deconstructor
    ~HexMap();

    // access to size information
    int width() const;
    int height() const;

    // access to tiles
    Tile& tile( int i );
    Tile& tile( int x, int y );
    Tile& operator[]( int i );
    Tile& operator()( int x, int y );

    // just for debugging
    friend
    std::ostream& operator<<( std::ostream &, HexMap & );

private:
    // size information ( both 0 for null object )
    int _w, _h;

    // tile array
    Tile *_t;

private:
    void index_out_of_bounds_warning( int x, int y ) const;
};

#endif // HEX_MAP_HH
