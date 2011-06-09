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
Position::distanceTo( Position const & pos ) const {
    int dx = pos._x - _x;
    int dy = pos._y - _y;
    return max( max(dx,-dx),
                max( max(dy,-dy),
                max( (dy - dx), (dx -dy) ) ) );
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
