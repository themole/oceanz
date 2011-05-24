#include "city.hh"

City::City( std::string const & name ) {
    setName( name );
}

City::~City() {}

std::string const &
City::name() const {
    return _name;
}

void
City::setName( std::string const & name ) {
    if( name != "" )
        _name = name;
}
