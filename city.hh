#ifndef CITY_HH
#define CITY_HH

#include "position.hh"
#include "stock.hh"

#include <string>

class City {

public:
    enum tile_type {
        HARBOR,
        PRODUCTION,
        HOUSES
    };

public:
    explicit City( std::string const & name );
    virtual ~City();

    // acces to storage .. the so called stock
    Stock & stock();

protected:
    std::string _name;
    Stock _stock;
    std::map< Position, tile_type > _local;
};

#endif // CITY_HH
