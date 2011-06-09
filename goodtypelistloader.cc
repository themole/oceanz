#include "goodtypelistloader.hh"

GoodTypeListLoader::GoodTypeListLoader( std::istream & source )
    : TypeListLoader< GoodTypeList >( source ) {
}

void
GoodTypeListLoader::load( GoodTypeList & gtl ) const {
    struct {
        std::string name;
        unsigned weight;
        unsigned std_price;
        unsigned price_stability;
    } tmp;

    tmp.name = "";
    tmp.weight = 0;
    tmp.std_price = 0;
    tmp.price_stability = 0;

    std::string word = "";

    while( !_src.eof() ) {
        _src >> word;

        if( word == "name" ) {
            if( tmp.name != "" )
                gtl.add( GoodType( tmp.name, tmp.weight, tmp.std_price, tmp.price_stability ) );
            _src >> tmp.name;
            tmp.weight = 0;
            tmp.std_price = 0;
            tmp.price_stability = 0;
        } else if( word == "weight" )
            _src >> tmp.weight;
        else if( word == "std_price" )
            _src >> tmp.std_price;
        else if( word == "price_stability" )
            _src >> tmp.price_stability;
        else
            continue;
    }

    if( tmp.name != "" )
        gtl.add( GoodType( tmp.name, tmp.weight, tmp.std_price, tmp.price_stability ) );

}
