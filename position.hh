#ifndef POSITION_HH
#define POSITION_HH

#include <iostream>
#include <list>

class Position {

public:
    enum Direction {
        E, NE, NW, W, SW, SE
    };

public:
    explicit Position( int x = 0, int y = 0 );
    ~Position();

    int x() const;
    int y() const;

    void setX( int x );
    void setY( int y );

    Position & operator=( Position const & rhs );

    Position operator+( Position const & rhs ) const;
    Position & operator+=( Position const & rhs );

    bool operator==( Position const & p ) const;
    bool operator!=( Position const & p ) const;

    // comparison by the "sum" of the distance to (0,0)
    // and the position in the ring of same distance to (0,0)
    // the first in order would alsways be (x,0)
    // counting counter clockwise
    bool operator<( Position const & p ) const;
    bool operator<=( Position const & p ) const;
    bool operator>( Position const & p ) const;
    bool operator>=( Position const & p ) const;

    bool isNeighbor( Position const & p ) const;

    Position const neighbor( Direction d ) const;

    std::list< Position > allNeighbors() const;
    std::list< Position > allNeighborsIn( int xmin, int xmax, int ymin, int ymax  ) const;
    std::list< Position > allInRange( int range ) const;

    unsigned distanceToNull() const;
    unsigned distanceTo( Position const & p ) const;

    // is the "sum" of distance to (0,0) and the position
    // in the ring of same distance to (0,0)
    // - used for ordering
    unsigned ord() const;

    friend
    std::ostream & operator<<( std::ostream &, Position const & p );

private:
    int _x, _y;

    static int max( const int a, const int b );
};

#endif // POSITION_HH
