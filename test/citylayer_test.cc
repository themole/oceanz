#include "../citylayer.hh"

int main() {

	CityLayer cl( 20, 20 );
	City* c = new City( "new City" );

	cl( 5, 4, c );

	std::cout << "getting city out of citylayer:" << std::endl;
	if( cl( 5, 4 ) != 0 )
		std::cout << *cl( 5, 4 ) << std::endl;
}
