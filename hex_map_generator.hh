#ifndef HEX_MAP_GENERATOR_HH
#define HEX_MAP_GENERATOR_HH

#include "perlin.hh"
#include "hex_map.hh"

class HexMapGenerator {

public:
    HexMapGenerator( long seed = 0 );
    ~HexMapGenerator();

    void setPerlin( Perlin const & );

    void generate( HexMap & ) const;

private:
    Perlin _p;

private: // functions
    void generateTerrain( HexMap & ) const;
};

#endif // HEX_MAP_GENERATOR_HH
