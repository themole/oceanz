#include "city.hh"
#include <cmath>
#include <ctime>
#include <cstdlib>

City::City( std::string const & name )
    : _name( name ),
      _level( 1 ) {
}

City::~City() {
}

std::string const &
City::name() const {
    return _name;
}

void 
City::setName( std::string const & name ) {
    _name = name;
}
