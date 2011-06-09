#include "../position.hh"

#include <iostream>

int main() {
    Position p( 0, 0 );

    std::cout << "p = ( 0, 0 )" << std::endl;
    std::cout << "p.allNeighbors():" << std::endl;
    auto plist = p.allNeighbors();
    for( auto it = plist.begin(); it != plist.end(); it++ )
        std::cout << *it << std::endl;

    std::cout << std::endl << "p.allInRange():" << std::endl;
    plist = p.allInRange( 1 );
    for( auto it = plist.begin(); it != plist.end(); it++ )
        std::cout << *it << std::endl;

    std::cout << std::endl << "( 4, 5 ).distanceTo( 5, 4 ):" << std::endl;
    std::cout << Position( 4, 5 ).distanceTo( Position( 5, 4 ) ) << std::endl;
}
