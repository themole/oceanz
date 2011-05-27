#ifndef CITY_LAYER_HH
#define CITY_LAYER_HH

#include "city.hh"
#include "layer.hh"
#include "position.hh"

#include <map>

class CityLayer : public Layer {

public:
    CityLayer( int width, int height );
    virtual ~CityLayer();

    void addCity( int x, int y, City * );
    void remCity( int x, int y );
    void remCity( Position const & pos );

    bool isCity( int x, int y );


protected:
    // all cities
    std::map< Position, City* > _c;
    // position of cities
};

#endif // CITY_LAYER_HH
