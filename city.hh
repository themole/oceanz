#ifndef CITY_HH
#define CITY_HH

#include "position.hh"
#include "stock.hh"

#include <string>
#include <set>

class City {

public:
    typedef unsigned short city_id;

public:
    explicit City( int x, int y, std::string const & name );
    explicit City( Position const & pos, std::string const & name );

    ~City();

    city_id id() const;

    std::string const & name() const;
    Position const & position() const;
    unsigned level() const;

    void setName(std::string const & name );

    void levelUp();

    std::set< Position > const & localTiles() const;

    bool addLocalTile( Position const & pos );
    bool removeLocalTile( Position const & pos );


private:

    city_id _id;

    std::string _name;
    Position _pos;

    unsigned _level;

    // set of local tiles to determin local spread for city view
    std::set< Position > _local;

private:
    static city_id current_id;
};

#endif // CITY_HH
