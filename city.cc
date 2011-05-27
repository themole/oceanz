#include "city.hh"

City::City( std::string const & name ) {
    _name = name;
    _stock = Stock();
}

Stock &
City::stock() {
    return _stock;
}
