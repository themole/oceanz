#ifndef CITY_LAYER_HH
#define CITY_LAYER_HH

#include "city.hh"
#include "layer.hpp"

#include <map>

class CityLayer : public Layer< City* > {

public:
    CityLayer( unsigned sx, unsigned sy );
    virtual ~CityLayer();

    virtual value_type const & operator()( unsigned i );
    virtual value_type const & operator()( unsigned x, unsigned y );
    virtual value_type const & operator()( Position const & p );

    virtual void operator()( unsigned i, value_type const & );
    virtual void operator()( unsigned x, unsigned y, value_type const & );
    virtual void operator()( Position const & p, value_type const & );

    virtual bool valid() const;

protected:

    std::map< City*, Position > _c;
    City* null;
};

#endif // CITY_LAYER_HH
