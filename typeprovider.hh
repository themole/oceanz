#ifndef TYPEPROVIDER_HH
#define TYPEPROVIDER_HH

#include "goodtype.hh"
#include "goodtypelist.hh"
#include "goodtypelistloader.hh"
#include "shiptype.hh"
#include "shiptypelist.hh"
#include "shiptypelistloader.hh"

class TypeProvider {

public:
    static void loadGoodTypeList( GoodTypeListLoader const & );
    static void loadShipTypeList( ShipTypeListLoader const & );

    static GoodType const & goodType( std::string const & name );
    static ShipType const & shipType( std::string const & name );

private:
    static GoodTypeList _gtl;
    static ShipTypeList _stl;
};

#endif // TYPEPROVIDER_HH
