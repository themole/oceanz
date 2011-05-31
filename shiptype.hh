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
              unsigned sight_radius = 0,
              unsigned buy_cost = 0 );

    ~ShipType();

    unsigned movesPerTurn() const;
    unsigned capacity() const;
    unsigned sightRadius() const;
    unsigned buyCost() const;

private:
    unsigned _moves_per_turn;        
    unsigned _capacity;
//    unsigned _min_crew;
//    unsigned _cannon_slots;
//    unsigned _max_leaks;
//    unsigned _speed_cost_per_leak;
    unsigned _sight_radius;
    unsigned _buy_cost;
//    unsigned _build_cost;
//    unsigned _build_time;
//    unsigned _upgrade_cost;
};

#endif // SHIP_TYPE_HH
