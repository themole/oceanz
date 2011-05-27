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
    typedef unsigned short amount_type;

    static const amount_type STD_MAX        =  40;
    static const amount_type STD_GLOBAL_MAX = 100;

public:
    Stock();
    ~Stock();

    amount_type amount( Wares type ) const;
    amount_type max( Wares type ) const;
    amount_type globalAmount() const;
    amount_type globalMax() const;

    bool has( Wares type ) const;
    bool empty() const;
    bool full( Wares type ) const;
    bool full() const;

    // empties the stock without changing set maxima
    void clear();
    // completely resets -> clearing and reseting maxima
    void reset();

    // sets max of good type to max if amount is less than max
    // if not it does nothing
    void setMax( amount_type max, Wares type );
    // only changes global_max if global_amnt is
    // less than new max
    void setGlobalMax( amount_type max );

    // puts amount of type in and returns how much could not
    // be put in because of storage limitation
    amount_type putIn( amount_type amount, Wares type);

    // puts everything from stuff into this and returns
    // what could not be put in because of storage limitation
    Stock const putIn( Stock const & stuff );

    // takes out amount of type and returns how much could not be taken out
    amount_type takeOut( amount_type amount, Wares type );

    // takes out everything listed in 'stuff' and returns a stock
    // containing a list of things not taken out because of not
    // being inside in the first place
    Stock const takeOut( Stock const & stuff );

    // operators
    Stock const operator+( Stock const & rhs ) const;
    bool operator==( Stock const & rhs ) const;
    bool operator!=( Stock const & rhs ) const;

    // for debuggin
    friend std::ostream &
    operator<<( std::ostream &, Stock const & );


private:
    std::map< Wares, amount_type > _stock;
    // list of maximum storage for each good
    std::map< Wares, amount_type > _maxs;

    // sum of current stock
    unsigned global_amnt;
    // sum of stored goods must not be greater than this
    unsigned global_max;
};

#endif // STOCK_HH
