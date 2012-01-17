#include "../position.hh"

#include <iostream>
#include <set>

int main() {
    Position p( 0, 0 );
    std::cout << "p = ( 0, 0 )" << std::endl;
    std::cout << "p.allNeighbors():" << std::endl;
    auto plist = p.allNeighbors();
    for( auto it = plist.begin(); it != plist.end(); it++ )
        std::cout << *it << std::endl;

    std::cout << std::endl << "p.allInRange( 1 ):" << std::endl;
    plist = p.allInRange( 1 );
    for( auto it = plist.begin(); it != plist.end(); it++ )
        std::cout << *it << std::endl;

    std::cout << std::endl << "p.distanceToNull() = " << p.distanceToNull() << std::endl;

    std::cout << std::endl << "( 4, 5 ).distanceTo( 5, 4 ):" << std::endl;
    std::cout << Position( 4, 5 ).distanceTo( Position( 5, 4 ) ) << std::endl;

    std::cout << std::endl;
    std::set< Position > test_set;

    auto list = Position( 0, 0 ).allInRange( 4 );

    for( auto it = list.begin(); it != list.end(); it++ )
        test_set.insert( *it );

    for( auto it = list.begin(); it != list.end(); it++ )
        std::cout << "( " << it->x() << ", " << it->y() << " ).ord() = " << it->ord() << "\t( " << it->x() << ", " << it->y() << " ).dist() = " << it->distanceToNull() << std::endl;

    std::cout << std::endl << std::endl;

    for( auto it = test_set.begin(); it != test_set.end(); it++ )
        std::cout << "( " << it->x() << ", " << it->y() << " ).ord() = " << it->ord() << "\t( " << it->x() << ", " << it->y() << " ).dist() = " << it->distanceToNull() << std::endl;
}
