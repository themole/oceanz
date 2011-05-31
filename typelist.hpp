#ifndef TYPE_LIST_HH
#define TYPE_LIST_HH

#include <string>
#include <set>

template< typename T >
class TypeList {

public:
    typedef T type_class;

public:
    type_class const & get( std::string const & name ) const {
        auto it = _list.find( type_class( name ) );
        if( it == _list.end() )
            return type_class::null;
        return *it;
    }

    void add( type_class const & type ) {
        _list.insert( type );
    }
    
protected:
    std::set< type_class > _list;
};

#endif // TYPE_LIST_HH
