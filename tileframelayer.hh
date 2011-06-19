#ifndef TILE_FRAME_LAYER_HH
#define TILE_FRAME_LAYER_HH

#include "layer.hh"
#include "surface.hh"
#include "tgafile.hh"
#include "position.hh"

#include <map>

enum tile_frame {
    WATER_00,
    LAND_00,
    LAND_10, LAND_11, LAND_12, LAND_13, LAND_14, LAND_15,
    LAND_20, LAND_21, LAND_22, LAND_23, LAND_24, LAND_25,
    LAND_30, LAND_31, LAND_32, LAND_33, LAND_34, LAND_35,
    LAND_40, LAND_41, LAND_42, LAND_43, LAND_44, LAND_45,
    LAND_50, LAND_51, LAND_52, LAND_53, LAND_54, LAND_55,
    LAND_60
};


class TileFrameLayer : public Layer {

public:
    TileFrameLayer( int sx, int sy );
    ~TileFrameLayer();

    Surface* frame( int x, int y );
    Surface* frame( Position const & p );
    Surface* frame( tile_frame id );

    void setFrame( tile_frame id, Surface* s );

private:
    std::map< unsigned, Surface* > _frames;
    tile_frame * _f;
};

#endif // TILE_FRAME_LAYER_HH
