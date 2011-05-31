#ifndef SHIPTYPELISTLOADER_HH
#define SHIPTYPELISTLOADER_HH

#include "shiptype.hh"
#include "shiptypelist.hh"
#include "typelistloader.hpp"

class ShipTypeListLoader : public TypeListLoader< ShipType > {

public:
    void load( ShipTypeList & stl ) const;
};

#endif // SHIPTYPELISTLOADER_HH
