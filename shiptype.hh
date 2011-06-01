#ifndef SHIP_TYPE_HH
#define SHIP_TYPE_HH

#include "typeclass.hh"

#include <string>

class ShipType : public TypeClass {

public:
    static const ShipType null;

public:
    ShipType( std::string const & name,
              unsigned moves_per_turn = 0,
              unsigned capacity = 0,
              unsigned min_crew = 0,
              unsigned cannon_slots = 0,
              unsigned max_leaks = 0,
              unsigned sight_radius = 0,
              unsigned buy_cost = 0,
              unsigned build_cost = 0,
              unsigned build_time = 0,
              unsigned upgrade_cost = 0,
              unsigned upgrade_time = 0 );

    ~ShipType();

    unsigned movesPerTurn() const;
    unsigned capacity() const;
    unsigned minCrew() const;
    unsigned cannonSlots() const;
    unsigned maxLeaks() const;
    unsigned sightRadius() const;
    unsigned buyCost() const;
    unsigned buildCost() const;
    unsigned buildTime() const;
    unsigned upgradeCost() const;
    unsigned upgradeTime() const;

private:
    unsigned _moves_per_turn;        
    unsigned _capacity;
    unsigned _min_crew;
    unsigned _cannon_slots;
    unsigned _max_leaks;
    unsigned _sight_radius;
    unsigned _buy_cost;
    unsigned _build_cost;
    unsigned _build_time;
    unsigned _upgrade_cost;
    unsigned _upgrade_time;
};

#endif // SHIP_TYPE_HH
