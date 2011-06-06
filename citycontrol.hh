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
    void upgradeCity( City * c );

private:
    WorldMap *_wm;
};

#endif // CITY_CONTROL_HH
