#ifndef REGION_HH
#define REGION_HH

#include <set>
#include <ostream>

enum region_type_bits { 
    WATER = 0x1,
    LAND  = 0x2,
    COAST = 0x4
};

typedef unsigned char region_type;

class Region {

public:
    Region( region_type );
    Region( Region const & r );
    ~Region();
    unsigned id() const;
    unsigned size() const;
    unsigned char type() const;
    bool is( region_type type ) const;

    std::set< Region* > connected() const;

    void setType( region_type type );
    void unsetType( region_type type );
    void setSize( unsigned size );
    void setConnected( Region * r );

    void unsetConnected( Region * r );

    void incrementSize();
    void decrementSize();

    bool operator<( Region const & rhs ) const;
    bool operator==( Region const & rhs ) const;

    // for debugging
    friend
    std::ostream & operator<<( std::ostream &, Region & );

private:
    unsigned _id;
    unsigned _sz;
    region_type _tp;

    std::set< Region* > _c; // connected Regions

    static unsigned current_id;
};

#endif // REGION_HH
