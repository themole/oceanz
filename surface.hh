#ifndef SURFACE_HH
#define SURFACE_HH

#include <GL/gl.h>

#include <string>

#include "stb_image.hh"

class
Surface {
public:

    typedef unsigned char byte;

    explicit
    Surface( int width, int height ) : _width( validate( width ) ),
                              _height( validate( height ) ),
                              _rowstride( _width*4 ),
                              _size( _width*_height*4 ),
                              _loaded_via_stb( false ) {

        data = new byte[ _size ];
    }

    Surface( std::string const & filename ) {
        data = stbi_load( filename.c_str(), &_width, &_height, &_rowstride, 0 );
        _rowstride *= _width;
        _size = _rowstride * _height;
        _loaded_via_stb = true;
    }

    /*
    template< typename Source >
    explicit
    Surface( Source const& s ) : _width( s.width() ),
                                 _height( s.height() ),
                                 _rowstride( _width*4 ),
                                 _size( _rowstride*_height ),
                                 _loaded_via_stb( false ) {

        data = new byte[ _size ];

        for( int i = 0; i < _size; ++i )
            data[ i ] = s.raw()[ i ];
    }
    */

    ~Surface() {
        if( _loaded_via_stb )
            stbi_image_free( data );
        else
            // Safe for primitive types:
            delete [] data;
    }

    // Raw data access, convenience for OpenGL:
    operator byte const*() {
        return data;
    }

    byte const*
    raw() const {
        return data;
    }

    void
    paint( Surface const& s, int x, int y ) {
        // TODO: Calculate overlapping rectangle.
        

        for( int u = 0; u < s._width; ++u ) {
            for( int v = 0; v < s._height; ++v ) {
                if( u + x >= _width || u + x < 0 ) continue;
                if( v + y >= _height || v + y < 0 ) continue;

                // TODO: Check for boundaries and discard invalid pixels.
                // Speeds things up.

                combine( s.get( u, v ),
                         get( u + x, v + y ) );
            }
        }
    }

    void
    clear( byte b, byte g, byte r, byte a ) {
        for( int i = 0; i < _size; ) {
            data[ i++ ] = b;
            data[ i++ ] = g;
            data[ i++ ] = r;
            data[ i++ ] = a;
        }
    }

    int
    width() const {
        return _width;
    }

    int
    height() const {
        return _height;
    }

protected:

    int _width;
    int _height;
    int _rowstride;
    int _size;

    bool _loaded_via_stb;

    byte* data;

    // Returns a valid dimension in any case:
    int
    validate( int x ) {
        if( x < 1 ) x = 1;
        else if( x > 0xFFFF ) x = 0xFFFF;
        return x;
    }

    typedef byte* fragment;

    // Combines two pixels to one using the alpha value:
    void
    combine( const fragment src, fragment dst ) {
        // Boundary check:
        if( !src || !dst ) return;

        // Same as OpenGL (SRC_ALPHA, ONE_MINUS_SRC_ALPHA):
        byte src_alpha = alpha( src );
        byte dst_alpha = 0xFF - src_alpha;

        put( dst,
             mul( blue( src ), src_alpha ) + mul( blue( dst ), dst_alpha ),
             mul( green( src ), src_alpha ) + mul( green( dst ), dst_alpha ),
             mul( red( src ), src_alpha ) + mul( red( dst ), dst_alpha ),
             src_alpha + dst_alpha );
    }

    // Sets the given fragment to the given color:
    void
    put( fragment f, byte b, byte g, byte r, byte a ) {
        *( f++ ) = r; *( f++ ) = g; *( f++ ) = b;
        *f = a;
    }

    // Sets the fragment at (x, y) to the given color:
    void
    put( int x, int y, byte b, byte g, byte r, byte a ) {
        if( x >= _width || y >= _height ) return;
        fragment f = &data[ y*_rowstride + x*4 ];
        put( f, r, g, b, a );
    }

    // Returns the fragment at position (x, y), or a null pointer if out of range:
    fragment
    get( int x, int y ) {
        if( x >= _width || y >= _height ) return 0;
        return &data[ y*_rowstride + x*4 ];
    }

    fragment
    get( int x, int y ) const {
        if( x >= _width || y >= _height ) return 0;
        return &data[ y*_rowstride + x*4 ];
    }

    // Simplified fixed-point multiplication for unsigned bytes:
    byte
    mul( byte x, byte y ) {
        return ( static_cast< unsigned short >( x )*static_cast< unsigned short >( y ) )/0xFF;
    }

    // Helper functions for color access:
    byte blue( fragment x ) { return *( x + 2 ); }
    byte green( fragment x ) { return *( x + 1 ); }
    byte red( fragment x ) { return *( x ); }
    byte alpha( fragment x ) { return *( x + 3 ); }
};

#endif // SURFACE_HH
