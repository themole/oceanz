#ifndef GOOD_TYPE_HH 
#define GOOD_TYPE_HH

#include "typeclass.hh"

#include <string>

class GoodType : public TypeClass {

public:
    static const GoodType null;

public:
    GoodType( std::string const & name,
             unsigned weight = 0,
             unsigned std_price = 0,
             unsigned price_stability = 0 );

    GoodType( GoodType const & );

    ~GoodType();

    unsigned weight() const;
    unsigned std_price() const;
    unsigned price_stability() const;

    
protected:
    unsigned _weight;
    unsigned _std_price;
    unsigned _price_stability;

    GoodType();
};

#endif // GOOD_TYPE_HH
