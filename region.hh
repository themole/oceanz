#ifndef REGION_HH
#define REGION_HH

#include <set>

enum region_type { 
    WATER,
    LAND,
    COAST
};

class Region {

public:
    Region( region_type type );
    ~Region();

    unsigned id() const;
    unsigned size() const;
    region_type type() const;

    std::set< Region* > connected() const;

    void setType( region_type type );
    void setSize( unsigned size );
    void setConnected( Region * r );

    void incrementSize();
    void decrementSize();

private:
    unsigned _id;
    unsigned _sz;
    region_type _tp;

    std::set< Region* > _c; // connected Regions

    static unsigned current_id;
};

#endif // REGION_HH
