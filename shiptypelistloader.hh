#ifndef SHIPTYPELISTLOADER_HH
#define SHIPTYPELISTLOADER_HH

#include "shiptypelist.hh"
#include "typelistloader.hpp"

#include <istream>

class ShipTypeListLoader : public TypeListLoader< ShipTypeList > {

public:
    ShipTypeListLoader( std::istream & );
    void load( ShipTypeList & stl ) const;
};

#endif // SHIPTYPELISTLOADER_HH
