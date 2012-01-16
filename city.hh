#ifndef CITY_HH
#define CITY_HH

#include "position.hh"
#include "stock.hh"

#include <string>
#include <list>

class City {

public:
    typedef unsigned short city_id;
    typedef std::list< Position > pos_list;

public:
    explicit City( std::string const & name );
    ~City();

    std::string const & name() const;
    std::list< Position > positions() const;
    city_id id() const;

    void setName(std::string const & name );


private:
    
    city_id _id;
    std::string _name;
    unsigned _level;

    std::list< Position > _ps;

private:
    static city_id current_id;
};

#endif // CITY_HH
