#ifndef REGION_MAP
#define REGION_MAP

#include "heightlayer.hh"
#include "position.hh"

#include <map>

// represents a complete decomposition of a HeightLayer into groups
// with different types ... accomplished by connected component analasys

class RegionLayer {

public:
    enum region_type {
        LAND,
        LAND_LOW,
        LAND_MID,
        LAND_HIGH,
        WATER,
        WATER_SHALLOW,
        WATER_MID,
        WATER_DEEP,
        COAST,
        NONE
    };

public:
    // generates null object
    RegionLayer();
    RegionLayer( HeightLayer const & hmap );
    ~RegionLayer();

    // access to size information
    int sizeX() const;
    int sizeY() const;

    // access to region information
    unsigned region( int x, int y ) const;
    unsigned region( Position const & ) const;

    void setRegion( int x, int y, unsigned group, region_type type );
    void setRegion( int x, int y, unsigned group );

    // diverse functions: ======================================
    // access to region properties
    // returns 0 if region is not available
    unsigned regionSize( unsigned region ) const;
    unsigned regionSizeX( unsigned region ) const;
    unsigned regionSizeY( unsigned region ) const;
    int regionMinX( unsigned region ) const;
    int regionMaxX( unsigned region ) const;
    int regionMinY( unsigned region ) const;
    int regionMaxY( unsigned region ) const;

    // return NONE if region not available
    region_type regionType( unsigned region ) const;

    unsigned greatestRegion( region_type type ) const;

    unsigned regionCount() const;
    unsigned regionCount( region_type type ) const;

    // null check
    bool isNull() const;

private:
    int _sx, _sy;

    // per tile region number
    unsigned *_r;

    // set of all groups
    std::map< unsigned, region_type > _t;
    std::map< unsigned, unsigned > _s;

private:
    void init( HeightLayer const & );
    void uninit();

    void generateRegions( HeightLayer const & );
    region_type heightToRegionType( HeightLayer::height_type height ) const;

    void print() const;
};

#endif // REGION_MAP
