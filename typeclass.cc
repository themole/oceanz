#include "typeclass.hh"

const TypeClass TypeClass::null = TypeClass();

TypeClass::TypeClass()
    : _name( "" ) {
}

TypeClass::TypeClass( std::string const & name )
    : _name( name ) {
}

std::string const &
TypeClass::name() const {
    return _name;
}

bool
TypeClass::operator<( TypeClass const & rhs ) const {
    return _name < rhs._name;
}
