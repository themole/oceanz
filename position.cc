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

bool Position::operator<( Position const & p ) const {
    return _x/(_y+74131.f) < p._x/(p._y+74131.f);
}
