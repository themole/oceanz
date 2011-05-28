#ifndef HARBOR_HH
#define HARBOR_HH

#include "building.hh"
#include "stock.hh"

class Harbor : public Building {

public:
    Harbor();
    virtual ~Harbor();

    virtual Stock const upgrade( Stock & s );

    static Stock const upgradeCost( unsigned level );
    static Stock const buildCost();
};

#endif // HARBOR_HH
