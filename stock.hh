#ifndef STOCK_HH
#define STOCK_HH

#include "goodtype.hh"

#include <list>
#include <string>

class Stock {

public:
    typedef unsigned short amount_type;
    typedef std::pair< GoodType const &, amount_type > type_amount_pair;

public:
    Stock( amount_type capacity = 0 );
    ~Stock();

    amount_type capacity() const;
    void setCapacity( amount_type capacity );

    amount_type amount( GoodType const & ) const;

    bool has( GoodType const & ) const;

    amount_type putIn( amount_type amount, GoodType const & type );
    amount_type takeOut( amount_type amount, GoodType const & type );


    bool full() const;
    bool empty() const;

private:
    amount_type _capacity;
    amount_type _current;
    std::list< type_amount_pair > _stuff;
};

#endif // STOCK_HH
