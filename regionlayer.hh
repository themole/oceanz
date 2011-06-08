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
    typedef std::list< Region > region_list;
    typedef std::list< Region >::iterator region_iterator;

public:
    RegionLayer( HeightLayer const & hmap );
    ~RegionLayer();

    // access to size information

    // access to region information
    Region * region( int x, int y );
    Region * region( Position const & );

    void setRegion( int x, int y, unsigned id );
    void setNewRegion( int x, int y, region_type type );

    // acces to region list
    region_iterator findRegion( unsigned id );

    void print();
private:

    // storing all regions
    // is kept sorted --> hopefully
    region_list _rs;
    // array of region pointer to elements of _rs
    // or 0
    Region **_ra;

private:

    void init( HeightLayer const & );
    void uninit();

    void generateRegions( HeightLayer const & );
    region_type heightToRegionType( HeightLayer::height_type height ) const;

};

#endif // REGION_LAYER_HH
