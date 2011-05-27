#ifndef REGION_MAP
#define REGION_MAP

#include "heightmap.hh"
#include "position.hh"

#include <map>

// represents a complete decomposition of a HeightMap into groups
// with different types ... accomplished by connected component analasys

class RegionMap {

public:
    enum region_type {
        LAND,
        WATER,
        COAST,
        NONE
    };

public:
    // generates null object
    RegionMap();
    RegionMap( HeightMap const & hmap );
    ~RegionMap();

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
    unsigned regionSize( unsigned group ) const;

    // return NONE if region not available
    region_type regionType( unsigned group ) const;

    unsigned greatestRegion( region_type type ) const;

    unsigned regionCount() const;
    unsigned groupCount( region_type type ) const;

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
    void init( HeightMap const & );
    void uninit();

    void connected_component_analasys( HeightMap const & );
    region_type heightToRegionType( short height ) const;

    void print() const;
};

#endif // REGION_MAP
