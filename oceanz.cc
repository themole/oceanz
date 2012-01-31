#include "./qt/mainwindow.hh"

#include "mapgenerator.hh"
#include "controlprovider.hh"
#include "citycontrol.hh"

#include <cmath>
#include <ctime>
#include <cstdlib>

#include <QApplication>

int main( int argc, char** argv ) {
    QApplication app( argc, argv );
    app.setQuitOnLastWindowClosed( true );

// create empty map
    int mapsize = 256;
    WorldMap *map = new WorldMap( mapsize, mapsize );

// world map initialization / generation

    srand( time( 0 ) );
    long seed = rand();

    Perlin p;
    p.setPersistence( .35 );
    p.setOctaves( 10 );
    p.setAmplitude( 65536 );
    p.setFreq0( pow( .5f, 5.6 ) );
    p.setSeed( seed );
    MapGenerator mapgen;
    mapgen.setPerlin( p );

    mapgen.generateMap( *map, .42f );
/*
    CityControl cc = CityControl( map );
    auto clist = map->cityLayer()->cities();
    for( unsigned i = 1; i <= 9; i++ ) {
        for( auto cit = clist.begin(); cit != clist.end(); cit++ ) {
            if( cit->second->level() == i && (unsigned)rand()%11 >= i+2 )
                cc.upgradeCity( cit->first );
        }
    }
    */

// setting up the window
    MainWindow main( 0 );

    main.setWorldMap( map );

    main.setWindowTitle( "Oceanz" );

    main.show();
    return app.exec();
}
