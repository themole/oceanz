#include <iostream>
#include <cmath>

#include "../city.hh"

int main() {
    std::cout << "CITY TEST:" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    std::cout << "  creating City 1:\t...\t";
    City city1( "City 1" );
    std::cout << "[OK]" << std::endl;
    std::cout << std::endl << city1;

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "  adding harbor to City 1:\t...\t";
    city1.stock().putIn( 20, SLAVES );
    city1.buildHarbor( city1.stock(), Position( 0, 1 ) );
    std::cout << "[OK]" << std::endl;
    std::cout << std::endl << city1;

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "  attempting to build harbor at same position:\t...\t";
    city1.stock().putIn( 20, SLAVES );
    city1.buildHarbor( city1.stock(), Position( 0, 1 ) );
    std::cout << "[OK]" << std::endl;
    std::cout << std::endl << city1;

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "  upgrading city!:\t...\t";
    city1.stock().putIn( 40, WOOD );
    std::list< Position > l;
    l.push_back( Position( 0,0 ).neighbor( Position::E ) );
    l.push_back( Position( 0,0 ).neighbor( Position::W ) );
    l.push_back( Position( 0,0 ).neighbor( Position::NE ) );
    l.push_back( Position( 0,0 ).neighbor( Position::SE ) );
    l.push_back( Position( 0,0 ).neighbor( Position::NW ) );
    l.push_back( Position( 0,0 ).neighbor( Position::SW ) );
    city1.upgrade( city1.stock(), l );
    std::cout << city1;

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "  upgrading city!:\t...\t";
    city1.stock().putIn( 40, WOOD );
    l.push_back( Position( 0,0 ).neighbor( Position::E ) );
    l.push_back( Position( 0,0 ).neighbor( Position::W ) );
    l.push_back( Position( 0,0 ).neighbor( Position::NE ) );
    l.push_back( Position( 0,0 ).neighbor( Position::SE ) );
    l.push_back( Position( 0,0 ).neighbor( Position::NW ) );
    l.push_back( Position( 0,0 ).neighbor( Position::SW ) );
    city1.upgrade( city1.stock(), l );
    std::cout << city1;

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "  adding harbor of City 1:\t...\t";
    city1.buildHarbor( city1.stock(), Position( -1, -1 ) );
    std::cout << "[OK]" << std::endl;
    std::cout << std::endl << city1;

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "  upgrading harbor at ( 0, 1 )\t...\t";
    city1.upgradeHarbor( city1.stock(), Position( 0, 1 ), l );
    std::cout << "[OK]" << std::endl;
    std::cout << std::endl << city1;
    

    std::cout << std::endl << Position( 1, 0 ).distanceTo( Position( 0, 1 ) )
        << std::endl;
}

