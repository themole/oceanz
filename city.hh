#ifndef CITY_HH
#define CITY_HH

#include "position.hh"
#include "stock.hh"

#include <string>
#include <list>
#include <map>

class Harbor {
public:
    Harbor() : hasProperty( false ) {}
    unsigned level() const { return _level; }
private:
    unsigned _level
    bool hasProperty; // and so on
};

class City {

public:
    // all Position information is considered to be in
    // local coordinates
    typedef std::list< Position > pos_list;

public:
    explicit City( std::string const & name );
    ~City();

    unsigned level() const;
    std::string const & name() const;

    void setName(std::string const & name );

    // list of all positions in local coordinates
    // the city occupies ... needs to be
    // interpreted by wiser operators ;-)
    pos_list const & local() const; 

    // adds new harbor at pos if possible
    // no other harbor is connected
    // and s contains enough resources
    Stock const buildHarbor( Stock & s, Position const & pos );

    // upgrades city .. takes needed resources out of stock and
    // grows to one or more positions given in validp
    // returns a stock containing everything that was not
    // enough to upgrade ... meaning what you need more in s than you did
    Stock const upgrade( Stock & s,
                           pos_list const & validp );

    // upgrades harbor at position and lets it grow to one of valid
    // if s does not contain the proper resources
    // the returned stock will contain what is missing
    // and Stock will be untouched
    Stock const upgradeHarbor( Stock & s,
                        Position const & pos,
                        pos_list const & validp );

    // acces to storage .. the so called stock
    Stock & stock();

    // for debuggin
    friend
    std::ostream & 
    operator<<( std::ostream & os, City const & );

protected:
    std::string _name;
    unsigned _level;
    // the storage
    Stock _stock;

    // local city form and size
    // ( 0, 0 ) is always part of this list => abandoned
    pos_list _loc;
    // position information of all a cities harbors
    std::map< Harbor*, pos_list > _h;


    // returns a stock with the amount of resources upgrading
    // would cost given the current state
    static Stock const upgradeCost( unsigned lvl );
    // returns how much a harbor costs
    static Stock const harborCost( unsigned hlvl ) const;
    // what does it cost to upgrade Harbor h
    Stock const upgradeHarborCost( Harbor *h ) const;

    static unsigned growth( unsigned level );
};

#endif // CITY_HH
