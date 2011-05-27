#include <set>
#include <iostream>

int main() {
    std::set< std::set< int > > sos;
    std::set< int > set1;
    std::set< int > set2;

    for( int i = 0; i < 5; i++ ) set1.insert( i*10 ), set2.insert( i*10 );
    set1.insert( 50 );

    sos.insert( set1 );
    sos.insert( set2 );

    for( auto it = sos.begin(); it != sos.end(); it++ ) {
        std::cout << "[ ";
        for( auto it2 = it->begin(); it2 != it->end(); it2++ )
            std::cout << *it2 << " ";
        std::cout << "]" << std::endl;
    }

    std::cout << std::endl;

    auto set1a = *sos.begin();
    sos.erase( set1a );
    set1a.insert( 50 );
    sos.insert( set1a );

    for( auto it = sos.begin(); it != sos.end(); it++ ) {
        std::cout << "[ ";
        for( auto it2 = it->begin(); it2 != it->end(); it2++ )
            std::cout << *it2 << " ";
        std::cout << "]" << std::endl;
    }
}
