#ifndef REGION_HH
#define REGION_HH

enum RegionType {
    LAND,
    WATER,
    COAST_LAND,
    COAST_WATER,
    NO_REGION
};

class Region {
    
public:
    Region( unsigned id, RegionType t );
    ~Region();

    unsigned size() const;
    unsigned id() const;
    RegionType type() const;

    void increaseSize( unsigned amnt );

    bool isLand() const;
    bool isWater() const;

    bool is( RegionType ) const;

    Region operator+( Region const & ) const;

    Region & operator=( Region const & );

private:
    unsigned _id;
    unsigned _sz;
    RegionType _t;

    Region();
};

#endif // REGION_HH
