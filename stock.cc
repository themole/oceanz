#include "stock.hh"

#include <ostream>

Stock::Stock() {
    _stock.clear();
    _maxs[ FOOD ] = STD_MAX;
    _maxs[ WOOD ] = STD_MAX;
    _maxs[ SLAVES ] = STD_MAX;
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
Stock::setMax( Wares type,  amnt_type max ) {
    _maxs[ type ] = max;
}

Stock::amnt_type
Stock::putIn( Wares type, amnt_type amount ) {
    std::map< Wares, amnt_type >::iterator ware = _stock.find( type );
    std::map< Wares, amnt_type >::iterator max = _maxs.find( type );
    amnt_type rest = max->second - ware->second - amount;
    if( rest <= 0 ) {
       ware->second += amount;
       rest = 0;
    } else {
        ware->second = max->second;
    }
    return rest;
}

std::ostream &
operator<<( std::ostream & os, Stock & s ) {
    std::map< Wares, Stock::amnt_type >::iterator wares = s._stock.begin();

    for( wares = s._stock.begin();
         wares != s._stock.end(); 
         wares++ ) {
        switch( wares->first ) {
            case FOOD:
                os << "food:\t"; break;
            case WOOD:
                os << "wood:\t"; break;
            case SLAVES:
                os << "slaves:\t"; break;
            default:
                os << "unknown:\t";
        }
        os << wares->second << "\t/ " << s._maxs[ wares->first ]
           << std::endl;
    }
    return os;
}
