#ifndef WORLDMAP_HH
#define WORLDMAP_HH

#include "heightlayer.hh"
#include "regionlayer.hh"
#include "citylayer.hh"

class WorldMap {

public:
    WorldMap( unsigned sx, unsigned sy );
    ~WorldMap();

    int sizeX() const;
    int sizeY() const;

    HeightLayer * heightLayer();
    RegionLayer * regionLayer();
    CityLayer * cityLayer();

    void setHeightLayer( HeightLayer * hl );
    void setRegionLayer( RegionLayer * rl );
    void setCityLayer( CityLayer * cl );

    HeightLayer::height_type height( int x, int y );
    HeightLayer::height_type height( Position const & pos );

    TerrainRegion * region( int x, int y );
    TerrainRegion * region( Position const & pos );

    City * city( int x, int y );
    City * city( Position const & pos );

private:
    int _sx, _sy;

    HeightLayer * _hl;
    RegionLayer * _rl;
    CityLayer * _cl;
};

#endif // WORLDMAP_HH
