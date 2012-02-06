#include "ship.hh"
#include "pathfinder.hh"

Ship::ship_id Ship::current_id = 1;

Ship::Ship( std::string const & name, Position const & pos )
    : _id( Ship::current_id++ ),
      _name( name ),
      _pos( pos ) {

    _path = Path();
    _stock = Stock();
}

Ship::~Ship() {
}

Ship::ship_id
Ship::id() const {
    return _id;
}

std::string
Ship::name() const {
    return _name;
}

Position const &
Ship::position() const {
    return _pos;
}

Path const & 
Ship::path() const {
    return _path;
}

bool
Ship::hasDestination() const {
    return !_path.empty();
}

void
Ship::setDestination( Position const & dest, WorldMap & map ) {
    _path = PathFinder::findPath( position(), dest, map );
    if( PathFinder::error() )
        std::cerr << "Ship " << _name << ": destination not reachable" << std::endl;
}

void
Ship::unsetDestination() {
    _path.clear();
}

void
Ship::move( int steps ) {
    if( _path.empty() || _path.current() == _path.end() || steps < 0 )
        return;

    for( int i = 0; i < steps; i++ )
        if( !_path.step() )
            _path.clear();
        else
            _pos = *_path.current();
}
