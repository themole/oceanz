#ifndef REGION_LAYER_HH
#define REGION_LAYER_HH

#include "layer.hh"
#include "region.hh"
#include "heightlayer.hh"
#include "position.hh"

#include <map>

// represents a complete decomposition of a HeightLayer into regions 
// with different types ... accomplished by connected component analasys

class RegionLayer : public Layer {

public:

public:
    RegionLayer( HeightLayer const & hmap );
    ~RegionLayer();

    // access to size information

    // access to region information
    Region * region( int x, int y ) const;
    Region * region( Position const & ) const;

    Region * regionByID( unsigned id ) const;

    void setRegion( int x, int y, Region * r );

    Region * greatestRegion( region_type type ) const;

    unsigned regionCount() const;
    unsigned regionCount( region_type type ) const;

    void print() const;
private:

    // storing all regions
    std::set< Region* > _rs;
    // array of region pointers to specify region for each hex
    Region **_ra;

private:

    void init( HeightLayer const & );
    void uninit();

    void generateRegions( HeightLayer const & );
    region_type heightToRegionType( HeightLayer::height_type height ) const;

};

#endif // REGION_LAYER_HH
