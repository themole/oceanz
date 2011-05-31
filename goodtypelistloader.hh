#ifndef GOODTYPELISTLOADER_HH
#define GOODTYPELISTLOADER_HH

#include "goodtypelist.hh"
#include "typelistloader.hpp"

class GoodTypeListLoader : public TypeListLoader< GoodTypeList > {

public:
    GoodTypeListLoader( std::istream & source );
    virtual void load( GoodTypeList & gtl ) const;
};

#endif // GOODTYPELISTLOADER_HH
