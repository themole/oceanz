#include "goodtype.hh"

const GoodType GoodType::null = GoodType();

GoodType::GoodType()
    : TypeClass() {
}

GoodType::GoodType( std::string const & name,
                  unsigned weight,
                  unsigned std_price,
                  unsigned price_stability )
    : TypeClass( name ),
      _weight( weight ),
      _std_price( std_price ),
      _price_stability( price_stability ) {
}

GoodType::GoodType( GoodType const & p )
    : TypeClass( p._name ),
      _weight( p._weight ),
      _std_price( p._std_price ),
      _price_stability( p._price_stability ) {
}

GoodType::~GoodType() {
}

unsigned
GoodType::weight() const {
    return _weight;
}

unsigned
GoodType::std_price() const {
    return _std_price;
}

unsigned
GoodType::price_stability() const {
    return _price_stability;
}

