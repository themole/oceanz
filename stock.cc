#include "stock.hh"

#include <ostream>

Stock::Stock() {
    reset();
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

Stock::amnt_type
Stock::globalAmount() const {
    return global_amnt;
}

Stock::amnt_type
Stock::globalMax() const {
    return global_max;
}

bool
Stock::has( Wares type ) const {
    if( _stock.find( type )->second > 0 )
        return true;
    return false;
}

bool
Stock::empty() const {
    return _stock.empty();
}

bool
Stock::full( Wares type ) const {
    auto good = _stock.find( type );
    auto max = _maxs.find( type );
    if( good != _stock.end() ) {
        if( good->second < max->second )
            return false;
        else
            return true;
    } else if( max->second == 0 )
        return true;
    else
        return false;
}


bool
Stock::full() const {
    if( global_amnt == global_max )
        return true;
    if( empty() )
        return false;
    for( auto good = _stock.begin();
         good != _stock.end();
         good++ ) {
        if( !this->full( good->first ) )
            return false;
    }
    return true;
}

void
Stock::clear() {
    _stock.clear();
    global_amnt = 0;
}

void
Stock::reset() {
    clear();
    setGlobalMax( STD_GLOBAL_MAX );
    setMax( STD_MAX, FOOD );
    setMax( STD_MAX, WOOD );
    setMax( STD_MAX, SLAVES );
}

void
Stock::setMax( amnt_type max, Wares type ) {
    if( _stock[ type ] <= max )
        _maxs[ type ] = max;
}

void
Stock::setGlobalMax( amnt_type max ) {
    if( global_amnt <= max )
        global_max = max;
}

Stock::amnt_type
Stock::putIn( amnt_type amount, Wares type ) {
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

    // ret is a pair of iterator and bool
    auto ret = _stock.insert( std::pair< const Wares, amnt_type >( type, amount ) );
    // my iterator
    auto good = ret.first;
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
Stock::putIn( Stock const & stuff ) {
    Stock not_put_in;
    not_put_in.setGlobalMax( 0 );
    for( auto good = stuff._stock.begin();
         good != stuff._stock.end();
         good++ ) {
        not_put_in.setGlobalMax( not_put_in.globalMax() + good->second );
        not_put_in.setMax( good->second, good->first );
        not_put_in.putIn( this->putIn( good->second, good->first ),
                          good->first );
    }
    return not_put_in;
}

Stock::amnt_type
Stock::takeOut( amnt_type amount, Wares type ) {
    auto good = _stock.find( type );
    if( good == _stock.end() )
        return amount;
    else {
        amnt_type not_taken = 0;
        if( amount > good->second ) {
            not_taken = amount - good->second;
            good->second = 0;
        } else 
            good->second -= amount;
        global_amnt -= amount - not_taken;
        return not_taken;
    }
}

Stock const
Stock::takeOut( Stock const & stuff ) {
    Stock not_taken;
    not_taken.setGlobalMax( 0 );
    for( auto good = stuff._stock.begin();
         good != stuff._stock.end();
         good++ ) {
        not_taken.setGlobalMax( not_taken.globalMax() + good->second );
        not_taken.setMax( good->second, good->first );
        not_taken.putIn( this->takeOut( good->second, good->first ),
                         good->first );
    }
    return not_taken;
}

Stock const
Stock::operator+( Stock const & rhs ) const {
    Stock ret;
    ret.setGlobalMax( globalMax() + rhs.globalMax() );
    for( auto good = _maxs.begin();
         good != _maxs.end();
         good++ ) { 
        ret.setMax( good->second + rhs.max( good->first ),
                    good->first );
    }
    ret.putIn( *this );
    ret.putIn( rhs );
    return ret;
}


std::ostream &
operator<<( std::ostream & os, Stock const & s ) {
    for( auto wares = s._stock.begin();
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
            os << wares->second << "\t/ " << s._maxs.find( wares->first )->second
           << std::endl;
    }
    os << "-------------------------------" << std::endl;
    os << "overall:\t" << s.global_amnt << "\t/ " << s.global_max << std::endl;
    return os;
}
