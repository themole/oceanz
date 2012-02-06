#ifndef SHIP_HH
#define SHIP_HH

#include "stock.hh"
#include "position.hh"
#include "path.hh"

#include <string>

class WorldMap;

class Ship {

public:
    typedef unsigned short ship_id;

private:
    static ship_id current_id;

public:

    Ship( std::string const & name, Position const & pos );
    ~Ship();


    ship_id          id() const;
    std::string      name() const;
    Position const & position() const;
    Path const &     path() const;

    Stock & stock();

    bool hasDestination() const;
    void setDestination( Position const & dest, WorldMap & map );
    void unsetDestination();

    void move( int steps );

protected:
    ship_id _id;
    std::string _name;
    Position _pos;
    Path _path;
    Stock _stock;
};

#endif // SHIP_HH
