#ifndef CITY_LAYER_HH
#define CITY_LAYER_HH

#include "city.hh"

#include <map>

class CityLayer {

public:
    CityLayer( int sx, int sy );
    ~CityLayer();

    int sizeX() const;
    int sizeY() const;

    City* city( int x, int y );
    void setCity( int x, int y, City* c );

    std::map< City*, Position > cities();

protected:
    int _sx, _sy;

    std::map< City*, Position > _c;
};

#endif // CITY_LAYER_HH
