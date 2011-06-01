#include "shiptype.hh"

const ShipType ShipType::null = ShipType("");

ShipType::ShipType( std::string const & name,
                    unsigned moves_per_turn,
                    unsigned capacity,
                    unsigned min_crew,
                    unsigned cannon_slots,
                    unsigned max_leaks,
                    unsigned sight_radius,
                    unsigned buy_cost,
                    unsigned build_cost,
                    unsigned build_time,
                    unsigned upgrade_cost,
                    unsigned upgrade_time )
    : TypeClass( name ),
      _moves_per_turn( moves_per_turn ),
      _capacity( capacity ),
      _min_crew( min_crew ),
      _cannon_slots( cannon_slots ),
      _max_leaks( max_leaks ),
      _sight_radius( sight_radius ),
      _buy_cost( buy_cost ),
      _build_cost( build_cost ),
      _build_time( build_time ),
      _upgrade_cost( upgrade_cost ),
      _upgrade_time( upgrade_time ) {
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
ShipType::minCrew() const {
    return _min_crew;
}

unsigned
ShipType::cannonSlots() const {
    return _cannon_slots;
}
unsigned
ShipType::maxLeaks() const {
    return _max_leaks;
}

unsigned
ShipType::sightRadius() const {
    return _sight_radius;
}

unsigned
ShipType::buyCost() const {
    return _buy_cost;
}

unsigned
ShipType::buildCost() const {
    return _build_cost;
}

unsigned
ShipType::buildTime() const {
    return _build_time;
}

unsigned
ShipType::upgradeCost() const {
    return _upgrade_cost;
}

unsigned
ShipType::upgradeTime() const {
    return _upgrade_time;
}
