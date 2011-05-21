
#include <iostream>

#include "perlin.hh"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <cmath>

int main() {
    Perlin p;

    srand( time( 0 ) );
    p.setSeed( rand() );

    float min = 0.f;
    float max = 0.f;
    float Noise = 0.f;

    float r = 2.f;

    for( float i = -2.f ; i <= 2.f; i += 0.0625/r ) {
    for( float j = -2.f ; j <= 2.f; j += 0.0625/r ) {
        Noise = p.Noise( i, j );
        std::cout << i << ", " << j << ", " << Noise << std::endl;
        if( min > Noise )
            min = Noise;
        if( max < Noise ) 
            max = Noise;
    }}

    std::cout << "min = " << min << std::endl
              << "max = " << max << std::endl;
    std::cout << "seed = " << p.seed() << std::endl;
}
