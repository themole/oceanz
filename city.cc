#include "city.hh"
#include <cmath>
#include <ctime>
#include <cstdlib>

City::city_id City::current_id = 1;

City::City( int x, int y, std::string const & name )
    : _id( City::current_id++ ),
      _name( name ),
      _pos( Position( x, y ) ),
      _level( 1 ) {

    if( _name == "" ) _name = "City " + _id;
    _local.insert( Position( 0, 0 ) );
}

City::City( Position const & pos, std::string const & name )
    : _id( City::current_id++ ),
      _name( name ),
      _pos( pos ),
      _level( 1 ) {
    
    if( _name == "" ) _name = "City " + _id;
    _local.insert( Position( 0, 0 ) );
}

City::~City() {
}

City::city_id
City::id() const {
    return _id;
}

std::string const &
City::name() const {
    return _name;
}

Position const &
City::position() const {
    return _pos;
}

unsigned
City::level() const {
    return _level;
}

void 
City::setName( std::string const & name ) {
    _name = name;
}

void
City::levelUp() {
    _level++;
}

std::set< Position > const &
City::localTiles() const {
    return _local;
}

bool
City::addLocalTile( Position const & tile ) {
    return _local.insert( tile ).second;
}

bool
City::removeLocalTile( Position const & tile ) {
    return _local.erase( tile ) == 1;
}
