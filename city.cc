#include "city.hh"
#include <cmath>
#include <ctime>
#include <cstdlib>

City::city_id City::current_id = 1;

City::City( std::string const & name )
    : _name( name ),
      _level( 1 ) {
    _ps.push_back( Position( 0, 0 ) );
    _id = City::current_id++;
}

City::~City() {
}

std::string const &
City::name() const {
    return _name;
}

std::list< Position >
City::positions() const {
    return _ps;
}

City::city_id
City::id() const {
    return _id;
}

void 
City::setName( std::string const & name ) {
    _name = name;
}

