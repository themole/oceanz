#ifndef TYPE_CLASS_HH
#define TYPE_CLASS_HH

#include <string>

class TypeClass {

public:
    static const TypeClass null;

public:
    TypeClass( std::string const & name );
    std::string const & name() const;
    bool operator<( TypeClass const & rhs ) const;

protected:
    std::string _name;

    TypeClass();
};

#endif // TYPE_CLASS_HH
