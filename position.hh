#ifndef POSITION_HH
#define POSITION_HH

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

    bool operator==( Position const & p ) const;
    bool operator!=( Position const & p ) const;

    Position const neighbor( Direction d ) const;

    unsigned distanceTo( Position const & p ) const;

private:
    int _x, _y;

    static int max( const int a, const int b );
};

#endif // POSITION_HH
