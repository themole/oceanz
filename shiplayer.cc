#include "shiplayer.hh"

ShipLayer::ShipLayer( int sx, int sy )
    : _sx( sx ), _sy( sy ) {

    if( _sx <= 0 || _sy <= 0 )
        _sx = 1, _sy = 1;
}

ShipLayer::~ShipLayer() {
    // responsable for all the ships created
    for( auto sit = _ships.begin(); sit != _ships.end(); sit++ ) {
        if( sit->second != 0 )
            delete sit->second;;;;
    }
    _ships.clear();
}

int
ShipLayer::sizeX() const {
    return _sx;
}

int
ShipLayer::sizeY() const {
    return _sy;
}

void
ShipLayer::newShip( std::string const & name, int x, int y ) {
    newShip( name, Position( x, y ) );
}

void
ShipLayer::newShip( std::string const & name, Position const & pos ) {
    if( pos.x() < 0 || pos.y() < 0 || pos.x() >= sizeX() || pos.y() >= sizeY() )
        return;

    Ship * new_ship = new Ship( name, pos );
    bool was_inserted = _ships.insert( std::pair< Ship::ship_id, Ship* >( new_ship->id(), new_ship ) ).second;
    if( !was_inserted )  {
        std::cerr << "shiplayer: unable to create new ship" << std::endl;
        delete new_ship;
    }
}

Ship *
ShipLayer::ship( Ship::ship_id id ) {
    auto sit = _ships.find( id );
    if( sit != _ships.end() )
        return sit->second;
    return 0;
}

Ship *
ShipLayer::ship( int x, int y ) {
    return ship( Position( x, y ) );
}

Ship *
ShipLayer::ship( Position const & pos ) {
    for( auto sit = _ships.begin(); sit != _ships.end(); sit++ ) {
        if( sit->second->position() == pos )
            return sit->second;
    }
    return 0;
}

void
ShipLayer::moveShips( int steps ) {
    for( auto sit = _ships.begin(); sit != _ships.end(); sit++ )
        sit->second->move( steps );
}
