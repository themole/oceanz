#ifndef TYPE_LIST_LOADER_HH
#define TYPE_LIST_LOADER_HH

#include <istream>

template< typename T >
class TypeListLoader {

public:
    typedef T type_class;

public:
    TypeListLoader( std::istream & source )
        : _src( source ) {
    }

    void load( type_class & ) const;

protected:
    std::istream & _src;
};

#endif // TYPE_LIST_LOADER_HH
