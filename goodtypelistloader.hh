#ifndef GOODTYPELISTLOADER_HH
#define GOODTYPELISTLOADER_HH

#include "goodtype.hh"
#include "goodtypelist.hh"
#include "typelistloader.hpp"

class GoodTypeListLoader : public TypeListLoader< GoodType > {

public:
    GoodTypeListLoader( std::istream & source );
    void load( GoodTypeList & gtl ) const;
};

#endif // GOODTYPELISTLOADER_HH
