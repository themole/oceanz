
#include "perlin.hh"

#include <climits>
#include <cmath>

float
Perlin::noise( float x ) const {

    // get integer left of x
    int intx = static_cast< int >( x );
    if( x < 0.f )
        intx--;

    // get distance of intx to x
    float fracx = x - intx;

    // get random gradiants at intx and intx+1
    // grad0 and grad1 will be in [-1.f, 1.f]
    float grad0 = 2.f * hash_float( intx     ) - 1.f;
    float grad1 = 2.f * hash_float( intx + 1 ) - 1.f;

    // get influences of gradients on x
    float s = grad0 * ( fracx      );
    float t = grad1 * ( fracx -1.f );

    // interpolate between influences
    return ease_perlin( s, t, fracx );
}

float
Perlin::noise( float x, float y ) const {
    int intx = static_cast< int >( x );
    int inty = static_cast< int >( y );
    if( x < 0.f ) intx--;
    if( y < 0.f ) inty--;

    float fracx = x - intx;
    float fracy = y - inty;

    // get 4 gradients ... one for each surrounding corner
    float g00x = 2.f * hash_float( intx    , inty    , 0 ) - 1.f; 
    float g10x = 2.f * hash_float( intx + 1, inty    , 0 ) - 1.f; 
    float g01x = 2.f * hash_float( intx    , inty + 1, 0 ) - 1.f;
    float g11x = 2.f * hash_float( intx + 1, inty + 1, 0 ) - 1.f;
    float g00y = 2.f * hash_float( intx    , inty    , 8 ) - 1.f;
    float g10y = 2.f * hash_float( intx + 1, inty    , 8 ) - 1.f;
    float g01y = 2.f * hash_float( intx    , inty + 1, 8 ) - 1.f;
    float g11y = 2.f * hash_float( intx + 1, inty + 1, 8 ) - 1.f;

    // influences (dot products)
    float s = g00x * ( fracx       ) + g00y * ( fracy       );
    float t = g10x * ( fracx - 1.f ) + g10y * ( fracy       );
    float u = g01x * ( fracx       ) + g01y * ( fracy - 1.f );
    float v = g11x * ( fracx - 1.f ) + g11y * ( fracy - 1.f );

    // interpolate
    // only differ in x
    float st = ease_perlin( s, t, fracx );
    float uv = ease_perlin( u, v, fracx );

    // only differ in y
    return ease_perlin( st, uv, fracy );
}

float
Perlin::noise( float x, float y, float z ) const {
    int intx = static_cast< int >( x );
    int inty = static_cast< int >( y );
    int intz = static_cast< int >( z );
    if( x < 0.f ) intx--;
    if( y < 0.f ) inty--;
    if( z < 0.f ) intz--;

    float fracx = x - intx;
    float fracy = y - inty;
    float fracz = z - intz;

    // get 8 gradients ... one for each surrounding corner
    // and their influences (dot-products)
    float g[2][2][2][3];
    float s[2][2][2];

    for( int i = 0; i <= 1; i++ )
        for( int j = 0; j <= 1; j++ )
            for( int k = 0; k <= 1; k++ ) {
                g[i][j][k][0] =
                    2.f * hash_float( intx + i, inty + j, intz + k, 0 ) - 1.f;
                g[i][j][k][1] =
                    2.f * hash_float( intx + i, inty + j, intz + k, 8 ) - 1.f;
                g[i][j][k][2] =
                    2.f * hash_float( intx + i, inty + j, intz + k, 16 ) - 1.f;
                
                s[i][j][k] =
                    g[i][j][k][0] * fracx - i
                  + g[i][j][k][1] * fracy - j
                  + g[i][j][k][2] * fracz - k;
            }
    
    // interpolate
    // differ only in x
    float x1 = ease_perlin( s[0][0][0], s[1][0][0], fracx );
    float x2 = ease_perlin( s[0][1][0], s[1][1][0], fracx );
    float x3 = ease_perlin( s[0][0][1], s[1][0][1], fracx );
    float x4 = ease_perlin( s[0][1][1], s[1][1][1], fracx );

    // differ only in y
    float xy1 = ease_perlin( x1, x2, fracy );
    float xy2 = ease_perlin( x3, x4, fracy );

    // differ only in z
    return ease_perlin( xy1, xy2, fracy );
}

float
Perlin::Noise( float x ) const {
    x = x;
    return 0.f;
}

float
Perlin::Noise( float x, float y ) const {
    float f = _freq_0;
    float a = _amplitude;
    float sum = 0.f;
    for( int i = 0; i < _octaves; i++ ) {
        sum += a * noise( f * x, f * y );
        f = f * 2.f;
        a = a * _persistence;
    }
    return sum;
}

float
Perlin::Noise( float x, float y, float z ) const {
    float f = _freq_0;
    float a = _amplitude;
    float sum = 0.f;
    for( int i = 0; i < _octaves; i++ ) {
        sum += a * noise( f * x, f * y, f * z );
        f = f * 2.f;
        a = a * _persistence;
    }
    return sum;
}

float
Perlin::tiling_noise( float x, float u ) const {
    return( noise( x ) * ( u - x ) + noise( x - u ) * x ) / u;
}

float
Perlin::tiling_noise( float x, float y, float u, float v ) const {
    return ( noise( x, y ) * ( u - x ) * ( v - y ) +
             noise( x - u, y ) * ( x ) * ( v - y ) +
             noise( x, y - v ) * ( x - u ) * ( y ) +
             noise( x - u, y - v ) * ( x ) * ( y ) ) /
             ( u * v );
}

float
Perlin::tiling_noise( float x, float y, float z, float u, float v, float w ) const {
    // TODO: implement
    return 0.f;
}

float
Perlin::tiling_Noise( float x, float u ) const {
    float f = _freq_0;
    float a = _amplitude;
    float sum = 0.f;
    for( int i = 0; i < _octaves; i++ ) {
        sum += a * ( noise( f * x ) * ( u - x ) + noise( f* x - u ) * x ) / u;
        f = f * 2.f;
        a = a * _persistence;
    }
    return sum;
}

float
Perlin::tiling_Noise( float x, float y, float u, float v ) const {
    float f = _freq_0;
    float a = _amplitude;
    float sum = 0.f;
    for( int i = 0; i < _octaves; i++ ) {
        sum += a * ( Noise( x, y ) * ( u - x ) * ( v - y ) +
                     Noise( x - u, y ) * ( x ) * ( v - y ) +
                     Noise( x, y - v ) * ( x - u ) * ( y ) +
                     Noise( x - u, y - v ) * ( x ) * ( y ) ) /
                     ( u * v );
        f = f * 2.f;
        a = a * _persistence;
    }
    return sum;
}

float
Perlin::tiling_Noise( float x, float y, float z, float u, float v, float w ) const {
    // TODO: implement
    return 0.f;
}

float
Perlin::ease_perlin( float a, float b, float x ) const {
    return a + ( b - a ) * x*x*( 3.f - 2.f * x );
}

float
Perlin::ease_perlin_improved( float a, float b, float x ) const {
    // TODO: implement
    return 0.f;
}

int
Perlin::hash_int( int a ) const {
    a -= ((a+_seed)<<6);
    a ^= (a>>17);
    a -= (a<<9);
    a ^= (a<<4);
    a -= (a<<3);
    a ^= (a<<10);
    a ^= (a>>15);
    return a;
}

int
Perlin::hash_int( int a, int b ) const {
    return hash_int( 67 * a + 71 * b );
}

int
Perlin::hash_int( int a, int b, int c ) const {
    return hash_int( 59 * a + 67* b + 61 * c );
}

float
Perlin::hash_float( int a ) const {
    return static_cast< float >( Perlin::hash_int( a ) ) / INT_MAX;
}

float
Perlin::hash_float( int a, int b, unsigned char bit ) const {
    int h = hash_int( a, b );
    h = (h >> bit ) & 0xff;
    return static_cast< float >( h ) / 0xff;
}

float
Perlin::hash_float( int a, int b, int c, unsigned char bit ) const {
    int h = hash_int( a, b, c );
    h = ( h >> bit ) & 0xff;
    return static_cast< float >( h ) / 0xff;
}
