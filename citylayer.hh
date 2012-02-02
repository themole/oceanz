#ifndef CITY_LAYER_HH
#define CITY_LAYER_HH

#include "city.hh"

#include <map>
#include <string>

class CityLayer {

public:

    // might find more in the future
    enum association_type {
        INSIDE,
        AROUND
    };

    // associative map to determin wheter or not a field
    // has a relation to a city and if yes what kind
    // empty means standart field
    typedef std::map< City::city_id, association_type > city_info;

public:
    CityLayer( int sx, int sy );
    ~CityLayer();

    int sizeX() const;
    int sizeY() const;

    unsigned cityCount() const;

    bool cityAt( int x, int y ) const;

    City::city_id insideCity( int x, int y ) const;
    bool aroundCity( int x, int y ) const;
    
    city_info cityInfo( int x, int y ) const;
    city_info cityInfo( Position const & ) const;

    void setCityInfo( int x, int y, City::city_id, association_type );
    void setCityInfo( Position const &, City::city_id id, association_type t );

    City* city( int x, int y );
    City* city( Position const & );
    City* city( City::city_id cid );

    std::map< City::city_id, City* > const & cities();

    void newCity( int x, int y, std::string const & name );

protected:
    // size of the map ... as in heightlayer and so on
    int _sx, _sy;
    // information for each field
    city_info *_ci;

    // map of all the cities
    std::map< City::city_id, City* > _cs;

private:


    void init( int sx, int sy );
    void uninit();
};

#endif // CITY_LAYER_HH
