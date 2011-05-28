#include "position.hh"

Position::Position( int x, int y ) :
    _x( x ), _y( y ) {
}

Position::~Position() {
}

int Position::x() const {
    return _x;
}

int Position::y() const {
    return _y;
}

void Position::setX( int x ) {
    _x = x;
}

void Position::setY( int y ) {
    _y = y;
}

Position & 
Position::operator=( Position const & rhs ) {
    _x = rhs._x;
    _y = rhs._y;
    return *this;
}

bool
Position::operator==( Position const & p ) const {
    return _x == p._x && _y == p._y;
}

bool
Position::operator!=( Position const & p ) const {
    return !operator==( p );
}

Position const
Position::neighbor( Direction d ) const {
    switch( d ) {
    case E:  return Position( _x+1, _y   );
    case NE: return Position( _x  , _y-1 );
    case NW: return Position( _x-1, _y-1 );
    case W:  return Position( _x-1, _y   );
    case SW: return Position( _x  , _y+1 );
    case SE: return Position( _x+1, _y+1 );
    }
    return Position();
}

unsigned
Position::distanceTo( Position const & pos ) const {
    int dx = pos._x - _x;
    int dy = pos._y - _y;
    return Position::max( dx, Position::max( dy, dy - dx ) );
}

int
Position::max( const int a, const int b ) {
    return ( a>b )? a : b;
}
