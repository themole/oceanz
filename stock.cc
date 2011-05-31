#include "stock.hh"

#include <ostream>

Stock::Stock( amount_type capacity )
    : _capacity( capacity ),
      _current( 0 ) {
}

Stock::~Stock() {
}

Stock::amount_type
Stock::putIn( amount_type amount, GoodType const & type ) {
    amount_type rest = 0;

    if( _current + amount > _capacity ) {
        rest = _current + amount - _capacity;
        amount = amount - rest;
    }

    _current += amount;

    auto it = _stuff.find( type.name() );
    if( it == _stuff.end() )
        _stuff.insert( std::pair< std::string, amount_type >( type.name(), amount ) );
    else
        it->second += amount;

    return rest;
}

Stock::amount_type
Stock::takeOut( amount_type amount, GoodType const & type ) {
    auto it = _stuff.find( type.name() );

    if( it == _stuff.end() )
        return amount;

    amount_type rest = 0;

    if( it->second < amount ) {
        rest = amount - it->second;
        amount = amount - rest;
    }

    it->second -= amount;
    return rest;
}

