#ifndef CITY_HH
#define CITY_HH

#include "stock.hh"

#include <string>

class City {

public:
    explicit City( std::string const & name );
    ~City();

    std::string const & name() const;
    Stock &             stock();

    void setName( std::string const & name );

private:
    std::string _name;
    Stock       _stock;
};

#endif // CITY_HH
