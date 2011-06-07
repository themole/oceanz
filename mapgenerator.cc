#include "mapgenerator.hh"

#include <cmath>
#include <set>
#include <ctime>
#include <cstdlib>

#ifndef PI
#define PI 3.141592653589
#endif

MapGenerator::MapGenerator( long seed ) {
    _p.setSeed( seed );
    _p.setAmplitude( 65536.f );
    _p.setPersistence( 0.26f );
    _p.setOctaves( 8 );
    _p.setFreq0( pow( .5f, 6.f ) );
}

MapGenerator::~MapGenerator() {
}

void MapGenerator::setPerlin( Perlin const & perlin ) {
    _p = perlin;
}

#include <vector>

void MapGenerator::generateMap( WorldMap & map, float land_amount ) const {
    generateHeightLayer( map, land_amount );
    generateRegionLayer( map );
    generateCityLayer( map );
}

void
MapGenerator::generateHeightLayer( WorldMap & map, float land_amount ) const {
    if( map.heightLayer() == 0 )
        map.setHeightLayer( new HeightLayer( map.sizeX(), map.sizeY() ) );

    HeightLayer & hmap = *map.heightLayer();
    float min = 0.f, max = 0.f;
    float noise = 0.f;

    // this is (y,x) later
    std::vector< std::vector< float > > tmp;

    for( int y = 0; y < hmap.sizeY(); y++ ) {
        tmp.push_back( std::vector< float >() );
        for( int x = 0; x < hmap.sizeX(); x++ ) {
            noise = _p.Noise( ( hmap.sizeY() - y + 2 * x ) * cos( PI / 6.f ),
                              ( 2 * y ) * sin( PI / 6.f ) + 1.f );
            if( noise < min )
                min = noise;
            if( noise > max )
                max = noise;

            tmp[y].push_back( noise );
        }
    }

    float w = min + land_amount * ( max - min );

    for( int y = 0; y < hmap.sizeY(); y++ )
        for( int x = 0; x < hmap.sizeX(); x++ ) {
            if( tmp[y][x] > w )
                hmap.setHeight( x,
                                y,
                                ( tmp[y][x] - w ) / ( max - w )
                                        * HeightLayer::HEIGHT_MAX );
            else
                hmap.setHeight( x,
                                y,
                                ( tmp[y][x] - w ) / ( min - w )
                                        * HeightLayer::HEIGHT_MIN );
        }
}

void
MapGenerator::generateRegionLayer( WorldMap & map ) const {
    map.setRegionLayer( new RegionLayer( *map.heightLayer() ) );
}

void
MapGenerator::generateCityLayer( WorldMap & map ) const {
    if( map.cityLayer() == 0 )
        map.setCityLayer( new CityLayer( map.sizeX(), map.sizeY() ) );
    // number of city ... for name .. no name generator for now
    int n = 1;

    for( int y = 0; y < map.sizeY(); y++ ) {
        for( int x = 0; x < map.sizeX(); x++ ) {

            int city_chance = 50;

            if( map.region( x, y ) != COAST )
                continue;

            // coast must be larger than 200 tiles
            if( map.regionLayer()->regionSize( map.regionLayer()->region( x, y ) ) < 200 )
                continue;

            if( map.regionLayer()->regionSize( map.regionLayer()->region( x, y ) ) < 8 )
                continue;

            // what kind of neighbor does the field have?
            // little amount of land -> higher chance
            // great amount of land -> higher chance
            // medium amount -> no chance benefit or penalty
                // amount fo land neighbors
                int ln = 0;
                Position p( x, y );
                std::list< Position > nlist = p.allNeighbors();
                for( auto it = nlist.begin(); it != nlist.end(); it++ ) {
                    if( it->x() < 0 || it->y() < 9 )
                        continue;
                    if( map.region( it->x(), it->y() ) == LAND )
                        ln++;
                }

                if( ln == 5 ) city_chance += 20;
                else if( ln <= 2 ) city_chance += 20;
                else
                    city_chance += 10;

            // look for other cities around
            // -> one around ... lower chance
            // -> none around ... higher chance
                std::list< Position > rlist = p.allInRange( 10 );
                int ncc = 0; // number of cities in sight
                for( auto it = rlist.begin(); it != rlist.end(); it++ ) {
                    if( map.city( it->x(), it->y() ) != 0 )
                        ncc++;
                }
                city_chance -= 45 * ncc;

                rlist = p.allInRange( 10 );
            // cities with more than one waterregion in sight get higher chance
                int nwr = 0; // number of water regions
                std::set< unsigned > regs; // region ids already counted
                for( auto it = rlist.begin(); it != rlist.end(); it++ ) {
                    if( it->x() < 0 || it->y() < 0 ) continue;
                    if( map.region( it->x(), it->y() ) == WATER )
                       if( regs.find( map.regionLayer()->region( it->x(), it->y() ) ) == regs.end() )  {
                           regs.insert( map.regionLayer()->region( it->x(), it->y() ) );
                           nwr++;
                       }
                }
                regs.clear();
                city_chance += (nwr-1) * 25;


                city_chance += rand()%30 - 10;

            if( city_chance >= 72 ) {
                map.cityLayer()->setCity( x, y, new City( "city" ) );
                n++;
            }
        }
    }

    std::cout << n << " cities built." << std::endl;
}
