#include "../typeprovider.hh"

#include <iostream>
#include <fstream>

void printGoodType( GoodType const & gt );

int main() {

    std::ifstream in( "goods.dat", std::ios::in );

    GoodTypeListLoader gtll( in );

    TypeProvider::loadGoodTypeList( gtll );

    std::cout << " trying to get what i just put in : " << std::endl;
    printGoodType( TypeProvider::goodType( "Wood" ) );
    printGoodType( TypeProvider::goodType( "Slave" ) );
}

void printGoodType( GoodType const & gt ) {
    std::cout << gt.name() << std::endl
              << " weight:\t"    << gt.weight() << std::endl
              << " std_price:\t" << gt.std_price() << std::endl
              << " prc_stab.:\t" << gt.price_stability() << std::endl << std::endl;
}
