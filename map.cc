#include "map.hh"
#include <utility>

Map::Map()
    : HeightMap() {}

Map::Map( int width, int height )
    : HeightMap( width, height ) {}

void
Map::save( std::string const & filename ) {
    HeightMap::save( filename + ".hmap" );
}

void
Map::load( std::string const & filename ) {
    HeightMap::load( filename + ".hmap" );
}

City*
Map::city( Position const & pos ) {
    auto c = _c.find( pos );
    if( c != _c.end() )
        return &c->second;
    else
        return 0;
}

City*
Map::city( int x, int y ) {
    return city( Position( x, y ) );
}

City*
Map::city( std::string const & name ) {
    for( auto it = _c.begin();
         it != _c.end();
         it++ )
        if( it->second.name() == name )
            return &it->second;

    return 0;
}

City*
Map::addCity( Position const & pos, std::string const & name ) {
    // ret is pair<iterator,bool>
    auto ret = _c.insert( std::pair< Position, City >( pos, City( name ) ) );
    // ret->second is bool
    if( ret.second )
        // ret->fist is iterator => ret->first->second is City
        return &ret.first->second;
    else return 0;
}

City*
Map::addCity( int x, int y, std::string const & name ) {
    return addCity( Position( x, y ), name );
}
