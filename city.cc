#include "city.hh"
#include <cmath>
#include <ctime>
#include <cstdlib>

City::City( std::string const & name )
    : _name( name ),
      _level( 1 ) {
    _ps.push_back( Position( 0, 0 ) );
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

std::list< Position >
City::positions() const {
    return _ps;
}
