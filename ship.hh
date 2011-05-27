#ifndef SHIP_HH
#define SHIP_HH

#include "occupant.hh"
#include "stock.hh"

class Ship : public Occupant {

public:

    Stock & stock();

    Stock cost() const;
    void setCost( Stock const & cost ) const;

protected:
    Stock _stock;
    
    static Stock _cost;
};

#endif // SHIP_HH
