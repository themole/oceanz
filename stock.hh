#ifndef STOCK_HH
#define STOCK_HH

#include "goodtype.hh"

#include <map>
#include <string>

class Stock {

public:
    typedef unsigned short amount_type;

public:
    Stock( amount_type capacity );
    ~Stock();

    amount_type putIn( amount_type amount, GoodType const & type );
    amount_type takeOut( amount_type amount, GoodType const & type );

    amount_type amount( GoodType const & );

    bool full() const;
    bool empty() const;

    amount_type capacity() const;

private:
    amount_type _capacity;
    amount_type _current;
    std::map< std::string, amount_type > _stuff;
};

#endif // STOCK_HH
