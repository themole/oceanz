#ifndef BUILDING_HH
#define BUILDING_HH

#include "stock.hh"

class Building {

public:
    static Stock const upgradeCost( unsigned level );
    static Stock const buildCost( unsigned level );

    Building();
    virtual ~Building();

    virtual unsigned level() const;
    virtual Stock const upgrade( Stock & s ) = 0;

protected:
    unsigned _level;
};

#endif // BUILDING_HH
