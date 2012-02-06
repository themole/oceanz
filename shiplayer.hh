#ifndef SHIP_LAYER_HH
#define SHIP_LAYER_HH

#include "position.hh"
#include "ship.hh"

#include <map>
#include <string>

class ShipLayer {
public:
    ShipLayer( int sx, int sy );
    ~ShipLayer();

    int sizeX() const;
    int sizeY() const; 

    void newShip( std::string const & name, int x, int y );
    void newShip( std::string const & name, Position const & pos );

    Ship * ship( Ship::ship_id id );
    Ship * ship( int x, int y );            // slow
    Ship * ship( Position const & pos );    // slow

    void moveShips( int steps );

private:
    int _sx, _sy;
    std::map< Ship::ship_id, Ship* > _ships;
};

#endif // SHIP_LAYER_HH
