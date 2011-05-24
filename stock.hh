#ifndef STOCK_HH
#define STOCK_HH

#include <map>
#include <ostream>

enum Wares {
    FOOD = 0,
    WOOD = 1,
    SLAVES = 46
};

class Stock {

public:
    static const unsigned STD_MAX = 40;

    typedef unsigned short amnt_type;

public:
    Stock();
    ~Stock();

    amnt_type amount( Wares type ) const;
    amnt_type max( Wares type ) const;
    bool has( Wares type ) const;

    void setMax( Wares type, amnt_type max );
    void setGlobalMax( amnt_type max );

    // puts amount of type in and returns how much could not
    // be put in because of storage limitation
    amnt_type putIn( Wares type, amnt_type amount );

    // puts everything from stuff into this and returns
    // what could not be put in because of storage limitation
    Stock const putIn( Stock & stuff );

    // takes out amount of type and returns how much could not be taken out
    unsigned takeOut( Wares type, amnt_type amount );

    // takes out everything listed in 'stuff' and returns a stock
    // containing a list of things not taken out because of not
    // being inside in the first place
    Stock const & takeOut( Stock & stuff );


    // for debuggin
    friend std::ostream &
    operator<<( std::ostream &, Stock & );


private:
    std::map< Wares, amnt_type > _stock;
    // list of maximum storage for each good
    std::map< Wares, amnt_type > _maxs;

    // sum of current stock
    unsigned global_amnt;
    // sum of stored goods must not be greater than this
    unsigned global_max;
};

#endif // STOCK_HH
