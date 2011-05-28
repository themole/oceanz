#include "city.hh"

City::City( std::string const & name ) {
    _name = name;
    _level = 1;
    _stock = Stock();

    _loc.push_back( Position( 0, 0 ) );
}

City::~City() {
    // delete all harbors
	for( auto it = _h.begin(); it != _h.end(); it++ )
		if( it->first != 0 )
			delete it->first;
}

unsigned
City::level() const {
    return _level;
}

std::string const &
City::name() const {
    return _name;
}

void
City::setName( std::string const & name ) {
    _name = name;
}

City::pos_list const &
City::local() const {
	return _loc;
}

Stock const
City::buildHarbor( Stock & s, Position const & pos ) {
    // not possible if s does not contain enough stuff:
    Stock rest = s.takeOut( harborCost() );

    if( !rest.empty() ) { // -> not enough resources in s
        std::cout << rest;
        s.putIn( harborCost() );
        s.takeOut( rest );
        return rest;
    }

    // harbor must not be too close to other harbors
    for( auto it = _h.begin(); it != _h.end(); it++ ) {
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ ) {
            if( it2->distanceTo( pos ) <= 1 ) {
                s.putIn( harborCost() );
                s.takeOut( rest );
                return rest;
            }
        }
    }

    // set up the pos list for the new harbor
    std::list< Position > l;
    l.push_back( pos );

    // insert it to the other harbors
    _h.insert( std::pair< Harbor*, pos_list >( new Harbor(), l ) );

    // insert position to the overall list
    _loc.push_back( pos );
    _loc.unique();
    return rest;
}

Stock const 
City::upgrade( Stock & s, pos_list const & validp ) {
    validp.empty();
    return s;
}

Stock const
City::upgradeHarbor( Stock & s,
                     Position const & p,
                     pos_list const & validp ) {
    p.x(); validp.empty();
    return s;
}

Stock &
City::stock() {
    return _stock;
}

Stock const 
City::upgradeCost() const {
    Stock cost;
    cost.putIn( _level * _level * 3, WOOD );
    return cost;
}

Stock const
City::harborCost() const {
    Stock cost;
    cost.putIn( 20, SLAVES );
    return cost;
}

std::ostream &
operator<<( std::ostream & os, City const & c ) {
    os << c._name << ": Level " << c.level() <<  std::endl;
    os << "Storage:" << std::endl;
    if( c._stock.empty() )
        os << "  is empty." << std::endl;
    else
        os << c._stock;
    os << "local position occupation:\n";
    for( auto it = c._loc.begin(); it != c._loc.end(); it++ ) {
        os << *it << " ";
    }
    os << std::endl;
    os << "harbor address and position occupation:\n";
    for( auto it = c._h.begin(); it != c._h.end(); it++ ) {
        os << "ard: " << it->first << "\t";
        for( auto it2 = it->second.begin(); it2 != it->second.end(); it2++ ) {
            os << *it2 << " ";
        }
        os << std::endl;
    }
    os << std::endl;

    return os;
}
