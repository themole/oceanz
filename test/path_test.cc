#include "../path.hh"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {

    srand( time( 0 ) );

    Path p;
    Position last = Position( 0, 0 );
    for( int i = 0; i < 100; i++ ) {
        p.add( last );
        int r = rand() % 6;
        switch( r ) {
            case 0: last = last.neighbor( Position::E  ); break;
            case 1: last = last.neighbor( Position::W  ); break;
            case 2: last = last.neighbor( Position::NE ); break;
            case 3: last = last.neighbor( Position::NW ); break;
            case 4: last = last.neighbor( Position::SE ); break;
            case 5: last = last.neighbor( Position::SW ); break;
        }
    }
    p.print();
}
