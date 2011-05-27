#ifndef MAP_GENERATOR_HH
#define MAP_GENERATOR_HH

#include "perlin.hh"
#include "heightmap.hh"

class MapGenerator {

public:
    MapGenerator( long seed = 0 );
    ~MapGenerator();

    void setPerlin( Perlin const & );

    void generate( HeightMap & ) const;

private:
    Perlin _p;

private: // functions
};

#endif // MAP_GENERATOR_HH
