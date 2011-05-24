#ifndef HEIGHT_MAP_HH
#define HEIGHT_MAP_HH

#include "position.hh"

// represents any kind of 2d height map

#include <ostream>

template< typename T = int >
class HeightMap {

public:
    typedef T height_type;

public:
    // creates a "null" object
    HeightMap();
    // creates width*height sized map
    HeightMap( int width, int height );
    // deconstructor
    ~HeightMap();

    // test for being null object
    bool isNull() const;

    // access to size information
    int sizeX() const;
    int sizeY() const;

    // access to height information
    height_type height( int x, int y ) const;
    height_type height( Position const & ) const;

    // access to tiles
    void save( std::string const & filename );
    void load( std::string const & filename );

    // just for debugging
    template< height_type >
    friend
    std::ostream& operator<<( std::ostream &, HeightMap< height_type > const & );

private:
    // size information ( both 0 for null object )
    int _sx, _sy;

    // height information
    height_type *_h;

    // un/initialization function ... just is comfortable
    void init( int sx, int sy, height_type h );
    void uninit();
};

#endif // HEIGHT_MAP_HH
