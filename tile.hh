#ifndef TILE_HH
#define TILE_HH

class Tile {

public:
    // initializes with any height
    Tile( int height = 0 );

    // access to height information
    int height() const;
    void setHeight( int height );

private:

    // height
    int _h;
};

#endif // TILE_HH
