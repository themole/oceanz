#ifndef REGION_HH
#define REGION_HH

#include <set>
#include <ostream>

enum region_type { 
    WATER,
    LAND,
    COAST
};

class Region {

public:
    Region( region_type type );
    Region( Region const & r );
    ~Region();

    unsigned id() const;
    unsigned size() const;
    region_type type() const;

    std::set< Region* > connected() const;

    void setType( region_type type );
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
