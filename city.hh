#ifndef CITY_HH
#define CITY_HH

#include "position.hh"
#include "stock.hh"

#include <string>
#include <list>

class City {

public:
    typedef std::list< Position > pos_list;

public:
    explicit City( std::string const & name );
    ~City();

    std::string const & name() const;

    void setName(std::string const & name );

private:
    std::string _name;
    unsigned _level;

};

#endif // CITY_HH
