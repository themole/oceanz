#ifndef CITY_HH
#define CITY_HH

#include "stock.hh"

#include <string>

class City {

public:
    explicit City( std::string const & name );
    ~City();

    // access to name
    std::string const & name() const;
    void setName( std::string const & name );

    // acces to storage .. the so called stock
    Stock & stock();

    bool operator<( City const & ) const;

private:
    std::string _name;
    Stock       _stock;
};

#endif // CITY_HH
