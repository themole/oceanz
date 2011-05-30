#ifndef CITY_CONTROL_HH
#define CITY_CONTROL_HH

#include "citylayer.hh"
#include "regionlayer.hh"

#include <string>

class CityControl {

public:
    CityControl( CityLayer &, RegionLayer const & );
    ~CityControl();

    void buildCity( Position const & p, std::string const & name );
    void upgradeCity( Position const & p );

private:
    CityLayer & _cl;
    RegionLayer const & _rl;
};

#endif // CITY_CONTROL_HH
