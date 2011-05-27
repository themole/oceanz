#ifndef OCCUPANT
#define OCCUPANT

#include <string>

class Occupant {

public:
    explicit Occupant( std::string const & name );
    virtual ~Occupant();

    // access to name
    std::string name() const;
    void setName(std::string const & name );

    // to be able to make stl containers of Occupants
    virtual
    bool operator<( Occupant const & rhs ) const;

protected:
    std::string _name;
};

#endif // OCCUPANT
