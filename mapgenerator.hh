#ifndef MAP_GENERATOR_HH
#define MAP_GENERATOR_HH

#include "perlin.hh"
#include "worldmap.hh"

class MapGenerator {

public:
    MapGenerator( long seed = 0 );
    ~MapGenerator();

    void setPerlin( Perlin const & );

    void generateMap( WorldMap &, float land_amount ) const;

    void generateHeightLayer( WorldMap &, float land_amount ) const;
    void generateRegionLayer( WorldMap & ) const;
    void generateCityLayer( WorldMap & ) const;

private:
    Perlin _p;

private:
    // functions
};

#endif // MAP_GENERATOR_HH
