#include "shiptype.hh"

const ShipType ShipType::null = ShipType("");

ShipType::ShipType( std::string const & name,
                    unsigned moves_per_turn,
                    unsigned capacity,
                    unsigned sight_radius,
                    unsigned buy_cost )
    : TypeClass( name ),
      _moves_per_turn( moves_per_turn ),
      _capacity( capacity ),
      _sight_radius( sight_radius ),
      _buy_cost( buy_cost ) {
}

ShipType::~ShipType() {
}

unsigned
ShipType::movesPerTurn() const {
    return _moves_per_turn;
}

unsigned
ShipType::capacity() const {
    return _capacity;
}

unsigned
ShipType::sightRadius() const {
    return _sight_radius;
}

unsigned
ShipType::buyCost() const {
    return _buy_cost;
}
