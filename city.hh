#ifndef CITY_HH
#define CITY_HH

#include <string>

class City {

public:
    explicit City( std::string const & name );
    ~City();

    std::string const & name() const;

    void setName( std::string const & name );

private:
    std::string _name;

};

#endif // CITY_HH
