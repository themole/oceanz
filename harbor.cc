#include "harbor.hh"
#include "stock.hh"

Harbor::Harbor()
    : Building() {
}

Harbor::~Harbor() {}

Stock const 
Harbor::upgrade( Stock & s ) {
    Stock rest = s.takeOut( upgradeCost( _level ) );
    if( !rest.empty() ) {
        s.putIn( upgradeCost( _level ) );
        s.takeOut( rest );
    } else
        _level++;

    return rest; // which is empty
}

// 1 WOOD / level + 1  for now
Stock const
Harbor::upgradeCost( unsigned level ) {
    Stock cost;
    cost.putIn( level + 1, WOOD );
    return cost;
}

Stock const
Harbor::buildCost() {
    Stock cost;
    cost.putIn( 20, SLAVES );
    return cost;
}
