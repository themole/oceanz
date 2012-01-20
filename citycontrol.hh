#ifndef CITY_CONTROL_HH
#define CITY_CONTROL_HH

#include "worldmap.hh"

#include <string>

class CityControl {

public:
    CityControl( WorldMap * wm );
    ~CityControl();

    void setWorldMap( WorldMap * wm );

    void buildCity( Position const & p, std::string const & name );
    void upgradeCity( City::city_id id );

private:
    WorldMap *_wm;

    void checkAroundCity( City *c, unsigned range );
};

#endif // CITY_CONTROL_HH
