#include "../stock.hh"
#include <iostream>
#include <string>

void printStock( std::string const &, Stock const & );

int main() {
//    std::cout << " ... creating Stock 1" << std::endl;
//    Stock s1;
//    printStock( "Stock 1", s1 );
//
//    std::cout << " ... putting in 20 slaves" << std::endl;
//    s1.putIn( 20, SLAVES );
//    printStock( "Stock 1", s1 );
//
//    std::cout << " ... taking out 12 slaves" << std::endl;
//    s1.takeOut( 12, SLAVES );
//    printStock( "Stock 1", s1 );
//
//    Stock::amount_type not_taken;
//
//    std::cout << " ... trying to take out 11 slaves" << std::endl;
//    not_taken = s1.takeOut( 11, SLAVES );
//    printStock( "Stock 1", s1 );
//    std::cout << " ... not taken out: \t" << not_taken << " slaves"
//            << std::endl << std::endl;
//
//    std::cout << " ... putting in 10 slaves and 8 wood" << std::endl;
//    s1.putIn( 10, SLAVES );
//    s1.putIn( 8, WOOD );
//    printStock( "Stock 1", s1 );
//
//    std::cout << " ... creating Stock 2" << std::endl;
//    Stock s2;
//    printStock( "Stock 2", s2 );

//    std::cout << " ... putting in some stuff" << std::endl;
//    s2.putIn( 20, SLAVES );
//    s2.putIn( 10, WOOD );
//    s2.putIn( 11, FOOD );
//    printStock( "Stock 2", s2 );

//    std::cout << " ... putting as much as is in Stock 1 into Stock 2"
//            << std::endl;
//    s2.putIn( s1 );
//    printStock( "Stock 1", s1 );
//    printStock( "Stock 2 = Stock 2 + Stock 1", s2 );
//
//    std::cout << " ... Stock 1 and Stock 2 are";
//    if(!( s1 == s2 ) )
//        std::cout << " not";
//    std::cout << " equal." << std::endl;
//
//    std::cout << " ... trying to take as much as is in Stock 2 out of Stock 1"
//            << std::endl;
//    Stock s3 = s1.takeOut( s2 );
//    printStock( "Stock 1", s1 );
//    printStock( "not taken", s3 );
//
//    std::cout << " ... reducing global max of Stock 1" << std::endl;
//    s1.setGlobalMax( 50 );
//    printStock( "Stock 1", s1 );
//
//    std::cout << " ... trying to put as much in Stock 1 as is in Stock 2"
//            << std::endl;
//    Stock not_put = s1.putIn( s2 );
//    printStock( "Stock 1", s1 );
//    std::cout << " --- Stock 1 is ";
//    if( s1.full() )
//        std::cout << "full" << std::endl;
//    else
//        std::cout << "not full" << std::endl;
//    printStock( "not put in", not_put );
//    std::cout << " --- not put in is ";
//    if( not_put.full() )
//        std::cout << "full" << std::endl;
//    else
//        std::cout << "not full" << std::endl;
//
//    s2.setGlobalMax( 500 );
//    while( !s2.full() ) {
//        s2.putIn( s1 );
//    }
//    printStock( "Stock 2 after filling", s2 );
//
//    printStock( "Stock 2 + Stock 1", s2 + s1 );
//
//    std::cout << " ... clearing Stocks" << std::endl;
//    s1.clear(), s2.clear(), s3.clear(), not_put.clear();
//    printStock( "Stock 1", s1 );
//    printStock( "Stock 2", s2 );
//    printStock( "not_taken", s3 );
//    printStock( "not_put", not_put );
}
//void printStock( std::string const & name, Stock const & stock ) {
//    if( stock.empty() )
//        std::cout << name << " is empty." << std::endl << std::endl;
//    else
//        std::cout << name << ":" << std::endl << stock << std::endl;
//}

