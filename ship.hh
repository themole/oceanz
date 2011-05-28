#ifndef SHIP_HH
#define SHIP_HH

#include "stock.hh"

class Ship {

public:

    Stock & stock();

protected:
    Stock _stock;
};

#endif // SHIP_HH
