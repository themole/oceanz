#ifndef MAP_HH
#define MAP_HH

#include "heightmap.hh"
#include "position.hh"
#include "city.hh"

#include <string>
#include <map>

class Map : public HeightMap {

private:
    // operator< for Position ... only possible if in some range
    struct pos_compare {
        pos_compare() {};
        bool operator()( Position const & a, Position const & b ) const {
            return (  ( a.x() + a.y() * 9791 )
                    < ( b.x() + a.y() * 9791 ) );
        }
    };

public:
    Map();
    Map( int width, int height );

    void save( std::string const & filename );
    void load( std::string const & filename );

    City* city( Position const & );
    City* city( int x, int y );
    City* city( std::string const & name );

    City* addCity( Position const & pos, std::string const & name );
    City* addCity( int x, int y, std::string const & name );

private:
    std::map< Position, City, pos_compare > _c;
};

#endif // MAP_HH
