#include "occupationmap.hh"

OccupationMap::OccupationMap( int width, int height ) {
    if( width > 0 && height > 0 ) {
        _sx = width, _sy = height;
        _o = new std::set< Occupant* >[];
    }
    else
        _sx = 0, _sy = 0, _o = 0;

}

OccupationMap::~OccupationMap() {
    if( _o )
        delete[] _o;
}

int
OccupationMap::sizeX() const {
    return _sx;
}

int 
OccupationMap::sizeY() const {
    return _sy;
}

std::set< Occupant* > const &
OccupationMap::occupants( int x, int y ) {
    if( _o == 0 )
        return std::set< Occupant* >();

    return _o[ ( x%_sx ) + _sx * ( y%_sy ) ];
}

void
OccupationMap::addOccupant( int x, int y, Occupant* o ) {
    if( _o == 0 )
        return;
    _o[ ( x%_sx ) + _sx * ( y%_sy ) ].insert( o );
}

void
OccupationMap::remOccupant( int x, int y, Occupant* o ) {
    if( _o == 0 )
        return;

    _o[ ( x%_sx ) + _sx * ( y%_sy ) ].erase( o );
}

void
OccupationMap::remOccupant( Occupant* o ) {
    if( _o == 0 )
        return;

    for( int i = 0; i < _sx * _sy; i++ )
        _o[i].erase( o );
}