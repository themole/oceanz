// draw a hex grid around 0,0 and mark all cells with their distance

#include <iostream>
#include <cmath>

int max( int a, int b ) { return (a<b)?b:a; }
int max( int a, int b, int c ) { return max( max( a, b ), c ); }
int abs( int a ) { return max( a, -a ); }

int main() {

    int s = 21;

    int hex_map[s][s];
    for( int i = 0; i < s; i++ ) 
        for( int j = 0; j < s; j++ ) {
            int a = i - s/2;
            int b = j - s/2;
            int c = b - a;
            hex_map[i][j] = max( abs(a), abs(b), abs(c) );
        }

    for( int i = 0; i < s; i++ ) { 
        for( int k = s-i; k > 0; k-- )
            std::cout << "  ";
        for( int j = 0; j < s; j++ ) {
            if( hex_map[i][j] < 10 )
                std::cout << " ";
            std::cout << hex_map[j][i] << " ";
        }
        std::cout << std::endl;
    }
}
