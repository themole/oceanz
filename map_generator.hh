#ifndef MAP_GENERATOR_HH
#define MAP_GENERATOR_HH

#include "perlin.hh"
#include "map.hh"

class MapGenerator {

public:
    MapGenerator( long seed = 0 );
    ~MapGenerator();

    void setPerlin( Perlin const & );

    void generate( Map & ) const;

private:
    Perlin _p;

private: // functions
    void generateTerrain( Map & ) const;
    void generateCities( Map & ) const;
};

#endif // MAP_GENERATOR_HH
