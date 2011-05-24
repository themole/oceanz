#ifndef POSITION_HH
#define POSITION_HH

class Position {
public:
    explicit Position( int x = 0, int y = 0 );
    ~Position();

    int x() const;
    int y() const;

    void setX( int x );
    void setY( int y );

private:
    int _x, _y;
};

#endif // POSITION_HH
