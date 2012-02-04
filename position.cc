#include "position.hh"
#include <iostream>

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

Position
Position::operator+( Position const & rhs ) const {
    return Position( _x + rhs._x, _y + rhs._y );
}

Position &
Position::operator+=( Position const & rhs ) {
    _x += rhs._x;
    _y += rhs._y;
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
// comparison is the sum of the distance to (0,0)
// and the position in the ring of same distance to (0,0)
// the first in order would alsways be (x,0)
// counting counter clockwise
bool 
Position::operator<( Position const & p ) const {
    return this->ord() < p.ord();
}

bool
Position::operator<=( Position const & p ) const {
    return this->ord() <= p.ord();
}

bool
Position::operator>( Position const & p ) const {
    return this->operator<( p );
}

bool
Position::operator>=( Position const & p ) const {
    return this->operator<=( p );
}

bool
Position::isNeighbor( Position const & p ) const {
    return this->distanceTo( p ) == 1;
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

std::list< Position >
Position::allNeighbors() const {
    std::list< Position > plist;
    plist.push_back( neighbor(  E ) );
    plist.push_back( neighbor( NE ) );
    plist.push_back( neighbor( NW ) );
    plist.push_back( neighbor(  W ) );
    plist.push_back( neighbor( SW ) );
    plist.push_back( neighbor( SE ) );
    return plist;
}

std::list< Position >
Position::allInRange( int range ) const {
    std::list< Position > plist;
    for( int x = -range; x <= range; x++ ) {
        for( int y = -range; y <= range; y++ ) {
            Position p( _x + x, _y + y );
            if( (int) p.distanceTo( *this ) <= range )
                plist.push_back( p );
        }
    }
    return plist;
}

unsigned
Position::distanceToNull() const {
    if( _x == 0 && _y == 0 ) return 0; 
    int dist = 0;
    if( _x == _y )
        dist = max( _x, -_x );
    else if( _x == -_y )
        dist = max( _x, -_x ) + max( _y, -_y );
    else if( ( _x > 0 && _y < 0 ) || ( _x < 0 && _y > 0 ) )
        dist = max( _x, -_x ) + max( _y, -_y );
    else 
        dist = max( max( _x, -_x ), max( _y, -_y ) );
    return dist;
}

unsigned
Position::distanceTo( Position const & pos ) const {
    int dx = pos._x - this->_x;
    int dy = pos._y - this->_y;

    return Position( dx, dy ).distanceToNull();
}

unsigned
Position::ord() const {
    int dist = this->distanceToNull();

    if( dist == 0 )
        return 0;

    int mul = 0;
    for( int i = dist-1; i >= 1; i-- )
        mul += i;

    unsigned plus = 0;

    if( _x >= _y && _y <= 0 ) 
        plus = 1*dist + 1 - _x;
    else if( _x == -dist )
        plus = 3*dist + 1 - _y;
    else if( _x <= _y )
        plus = 4*dist + 1 + _x;
    else
        plus = 6*dist + 1 - _y;

    return 6 * mul + plus;
}

int
Position::max( const int a, const int b ) {
    return ( a>b )? a : b;
}

std::ostream &
operator<<( std::ostream & os, Position const & p ) {
    os << "(" << p._x << ", " << p._y << ")";
    return os;
}
