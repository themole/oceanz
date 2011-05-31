#include "../goodtype.hh"
#include "../goodtypelist.hh"

#include <iostream>

void printGoodType( GoodType const & );

int main() {
    GoodType wood = GoodType( "Wood", 1, 20, 90 );
    GoodType slave = GoodType( "Slave", 5, 200, 10 );
    GoodTypeList gtl;
    gtl.add( wood );
    gtl.add( slave );

    printGoodType( gtl.get( "Wood" ) );
    printGoodType( gtl.get( "Honey" ) );
    printGoodType( gtl.get( "Slave" ) );
}

void printGoodType( GoodType const & gt ) {
    std::cout << "Name:\t"       << gt.name() << std::endl
              << " weight:\t"    << gt.weight() << std::endl
              << " std_price:\t" << gt.std_price() << std::endl
              << " prc_stab.:\t" << gt.price_stability() << std::endl;
}
