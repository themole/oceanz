#include "stock.hh"

#include <ostream>

Stock::Stock() {
    _stock.clear();
    _maxs[ FOOD ] = STD_MAX;
    _maxs[ WOOD ] = STD_MAX;
    _maxs[ SLAVES ] = STD_MAX;

    global_amnt = 0;
    global_max = 100;
}

Stock::~Stock() {}

Stock::amnt_type
Stock::amount( Wares type ) const {
    return _stock.find( type )->second;
}

Stock::amnt_type
Stock::max( Wares type ) const {
    return _maxs.find( type )->second;
}

bool
Stock::has( Wares type ) const {
    if( _stock.find( type )->second > 0 )
        return true;
    return false;
}

void
Stock::setMax( Wares type, amnt_type max ) {
    _maxs[ type ] = max;
}

void
Stock::setGlobalMax( amnt_type max ) {
    if( global_amnt <= max )
        global_max = max;
}

Stock::amnt_type
Stock::putIn( Wares type, amnt_type amount ) {
    amnt_type not_put_in = 0;
    // respect global maximum
    if( global_amnt + amount > global_max ) {
        not_put_in = global_amnt + amount - global_max;
        amount = amount - not_put_in;
        global_amnt = global_max;
    } else
        global_amnt += amount;
    // maximum amount allowed for this good
    amnt_type max = _maxs[ type ];
    // my iterator
    std::map< Wares, amnt_type >::iterator good;

    std::pair< std::map< Wares, amnt_type >::iterator, bool > ret;
    ret = _stock.insert( std::pair< const Wares, amnt_type >( type, amount ) );
    good = ret.first;
    // if not newly inserted
    if( !ret.second ) 
       good->second += amount; 
    // fix if more than allowed
    if( good->second > max ) {
        amount = good->second;
        good->second = max;
        global_amnt -= amount - max;
        not_put_in += amount - max; 
    } 
    return not_put_in;
}

Stock const
Stock::putIn( Stock & stuff ) {
    std::map< Wares, amnt_type >::iterator good;
    Stock not_put_in;
    for( good = stuff._stock.begin();
         good != stuff._stock.end();
         good++ ) {
        not_put_in.setMax( good->first, stuff._maxs[ good->first ] );
        not_put_in.putIn( good->first,
                          this->putIn( good->first, good->second ) );
    }
    return not_put_in;
}

std::ostream &
operator<<( std::ostream & os, Stock & s ) {
    os << "Stock contents:" << std::endl;
    std::map< Wares, Stock::amnt_type >::iterator wares;

    for( wares = s._stock.begin();
         wares != s._stock.end(); 
         wares++ ) {
        switch( wares->first ) {
            case FOOD:
                os << "food:\t\t"; break;
            case WOOD:
                os << "wood:\t\t"; break;
            case SLAVES:
                os << "slaves:\t\t"; break;
            default:
                os << "unknown:\t\t";
        }
        os << wares->second << "\t/ " << s._maxs[ wares->first ]
           << std::endl;
    }
    os << "overall:\t" << s.global_amnt << "\t/ " << s.global_max << std::endl;
    return os;
}
