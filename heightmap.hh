#ifndef HEIGHT_MAP_HH
#define HEIGHT_MAP_HH

#include "position.hh"

// represents any kind of 2d height map

#include <ostream>

class HeightMap {

public:

    typedef short height_type;
    static const height_type HEIGHT_MAX = -255;
    static const height_type HEIGHT_MIN = 255;

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

    void setHeight( int x, int y, height_type height );
    void setHeight( Position const &, height_type height );

    // access to tiles
    void save( std::string const & filename );
    void load( std::string const & filename );

    // just for debugging
    friend std::ostream& operator<<( std::ostream &, HeightMap const & );

protected:
    // size information ( both 0 for null object )
    int _sx, _sy;

    // height information
    height_type *_h;

private:
    // un/initialization function ... just is comfortable
    void init( int sx, int sy, height_type h );
    void uninit();
};

#endif // HEIGHT_MAP_HH
