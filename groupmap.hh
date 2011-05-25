#ifndef GROUP_MAP_HH
#define GROUP_MAP_HH

#include "heightmap.hh"
#include "position.hh"

#include <map>

// represents a complete decomposition of a HeightMap into groups
// with different types ... accomplished by connected component analasys

class GroupMap {

public:
    enum GroupType {
        LAND,
        WATER,
        COAST,
        NONE
    };

public:
    // generates null object
    GroupMap();
    GroupMap( HeightMap< short > const & hmap );
    ~GroupMap();

    // access to size information
    int sizeX() const;
    int sizeY() const;

    // access to group information
    unsigned group( int x, int y ) const;
    unsigned group( Position const & ) const;

    void setGroup( int x, int y, unsigned group, GroupType type );
    void setGroup( int x, int y, unsigned group );

    // diverse functions: ======================================
    // returns 0 if group is not available
    unsigned groupSize( unsigned group ) const;

    // return NONE if group not available
    GroupType groupType( unsigned group ) const;

    unsigned greatestGroup( GroupType type ) const;

    unsigned groupCount() const;
    unsigned groupCount( GroupType type ) const;

    // null check
    bool isNull() const;

private:
    int _sx, _sy;

    // per tile group number
    unsigned *_g;

    // set of all groups
    std::map< unsigned, GroupType > _t;
    std::map< unsigned, unsigned > _s;

private:
    void init( HeightMap< short > const & );
    void uninit();

    void connected_component_analasys( HeightMap< short > const & );
    GroupType heightToType( short height ) const;

    void print() const;
};

#endif // GROUP_MAP_HH
