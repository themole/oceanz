#include <iostream>

#include "perlin.hh"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <cmath>

int main() {
    Perlin p;

    srand( time( 0 ) );
    p.seed( rand() );

    float min = 0.f;
    float max = 0.f;
    float noise = 0.f;

    float r = 2.f;

    for( float i = -2.f ; i <= 2.f; i += 0.0625/r ) {
    for( float j = -2.f ; j <= 2.f; j += 0.0625/r ) {
        noise = p.noise( i, j );
        std::cout << i << ", " << j << ", " << sin(noise) << std::endl;
        if( min > noise )
            min = noise;
        if( max < noise ) 
            max = noise;
    }}

    std::cout << "min = " << min << std::endl
              << "max = " << max << std::endl;
    std::cout << "seed = " << p.seed() << std::endl;
}
