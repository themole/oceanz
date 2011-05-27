#ifndef OCCUPATION_MAP_HH
#define OCCUPATION_MAP_HH

#include "position.hh"
#include "occupant.hh"

#include <set>

class OccupationMap {

public:
    OccupationMap( int width, int height );
    ~OccupationMap(); 

    int sizeX() const;
    int sizeY() const;

    std::set< Occupant* > const & occupants( int x, int y );

    std::set< Position >  location( Occupant* o ) const;

    void addOccupant( int x, int y, Occupant* o );
    void remOccupatn( Occupant* o );

    bool isOccupied( int x, int y ) const;

    bool hasOccupant( int x, int y, Occupant* o ) const;
    bool hasOccupant( Occupant* o ) const;

private:
    int _sx, _sy;
    // array of pointer
    std::set< Occupant* > *_o;
};

#endif // OCCUPATION_MAP_HH
