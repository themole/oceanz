#include "city.hh"

City::City( std::string const & name ) {
    setName( name );
    _stock = Stock();
}

City::~City() {
}

std::string const &
City::name() const {
    return _name;
}

Stock &
City::stock() {
    return _stock;
}

void City::setName( std::string const & name ) {
    if( name != "" )
        _name = name;
}

bool City::operator<( City const & rhs ) const {
    return _name < rhs._name;
}
