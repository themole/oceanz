#include "stock.hh"

#include <ostream>

Stock::Stock( amount_type capacity )
    : _capacity( capacity ),
      _current( 0 ) {
}

Stock::~Stock() {
}

Stock::amount_type
Stock::capacity() const {
    return _capacity;
}

void
Stock::setCapacity( amount_type capacity ) {
    _capacity = capacity;
}

Stock::amount_type
Stock::amount( GoodType const & type ) const {
    auto it = _stuff.begin();
    for( ; it != _stuff.end(); it++ )
        if( it->first == type )
            break;

    if( it == _stuff.end() )
        return 0;
    else
        return it->second;
}

bool
Stock::has( GoodType const & type ) const {
    auto it = _stuff.begin();
    for( ;it != _stuff.end(); it++ )
        if( it->first == type )
            break;
    return it != _stuff.end();
}


Stock::amount_type
Stock::putIn( amount_type amount, GoodType const & type ) {
    amount_type rest = 0;

    if( _current + amount > _capacity ) {
        rest = _current + amount - _capacity;
        amount = amount - rest;
    }

    _current += amount;
    auto it = _stuff.begin();
    for( ;it != _stuff.end(); it++ )
        if( it->first == type )
            break;

    if( it == _stuff.end() )
        _stuff.push_back( type_amount_pair( type, amount ) );
    else
        it->second += amount;

    return rest;
}

Stock::amount_type
Stock::takeOut( amount_type amount, GoodType const & type ) {

    auto it = _stuff.begin();
    for( ; it != _stuff.end(); it++ )
        if( it->first == type )
            break;

    if( it == _stuff.end() )
        return amount;

    amount_type rest = 0;

    if( it->second < amount ) {
        rest = amount - it->second;
        amount = amount - rest;
        _stuff.erase( it );
        return rest;
    }

    it->second -= amount;
    return rest;
}

bool
Stock::empty() const {
    return _current == 0;
}

bool
Stock::full() const {
    return _current == _capacity;
}
