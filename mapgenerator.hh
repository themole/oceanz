#ifndef MAP_GENERATOR_HH
#define MAP_GENERATOR_HH

#include "perlin.hh"
#include "worldmap.hh"

class MapGenerator {

public:
    MapGenerator( long seed = 0 );
    ~MapGenerator();

    void setPerlin( Perlin const & );

    void generateMap( WorldMap &, float land_amount );

    void generateHeightLayer( WorldMap &, float land_amount );
    void generateRegionLayer( WorldMap & );
    void generateCityLayer( WorldMap & );

private:
    Perlin _p;

private:
    // functions
};

#endif // MAP_GENERATOR_HH
