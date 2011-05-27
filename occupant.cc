#include "occupant.hh"

Occupant::Occupant( std::string const & name ) {
    setName( name );
}

Occupant::~Occupant() {
}

std::string
Occupant::name() const {
    return _name;
}

void
Occupant::setName( std::string const & name ) {
    _name = name;
}

bool
Occupant::operator<( Occupant const & rhs ) const {
    return _name < rhs._name;
}

