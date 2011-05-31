#include "shiptypelistloader.hh"

ShipTypeListLoader::ShipTypeListLoader( std::istream & src )
    : TypeListLoader( src ) {
}

void
ShipTypeListLoader::load( ShipTypeList & stl ) const {
    stl.get( "Brigg" );
}
