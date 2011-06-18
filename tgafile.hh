#ifndef TGA_FILE_HH
#define TGA_FILE_HH

#include <iostream>

#include <string>
#include <fstream>

class
TGAFile {
public:

    typedef unsigned char byte;

    explicit
    TGAFile( std::string const& filename ) {
        typedef unsigned char byte;
        std::ifstream in( filename.c_str() );

        if( !in.is_open() ) {
            dummy();
            return;
        }

        // Read header data:
        char header_data[ 18 ];
        in.read( header_data, 18 );

        unsigned id_length;
        id_length = static_cast< unsigned >( header_data[ 0 ] );

        unsigned color_map_type;
        color_map_type = static_cast< unsigned >( header_data[ 1 ] );
        if( color_map_type ) {
            dummy();
            return;
        }

        unsigned image_type;
        image_type = static_cast< unsigned >( header_data[ 2 ] );

        if( image_type != 2 ) {
            dummy();
            return;
        }

        unsigned width = twobyte( header_data[ 12 ], header_data[ 13 ] );
        unsigned height = twobyte( header_data[ 14 ], header_data[ 15 ] );
        unsigned bits_per_pixel = static_cast< unsigned >( header_data[ 16 ] );

        if( bits_per_pixel != 32 ) {
            dummy();
            return;
        }

        _width = static_cast< int >( width );
        _height = static_cast< int >( height );
        unsigned size = _width*_height*4;
        data = new byte[ size ];

        char buffer[ 256 ];
        in.read( buffer, id_length );
        in.read( reinterpret_cast< char* >( data ), size );
    }

    int
    width() const {
        return _width;
    }

    int
    height() const {
        return _height;
    }

    byte const*
    raw() const {
        return data;
    }

private:

    int _width;
    int _height;
    byte* data;

    void
    dummy() {
        _width = 10;
        _height = 10;
        data = new byte[ _width*_height*4 ];
        for( int i = 0; i < 400; ) {
            data[ i++ ] = 0x00;
            data[ i++ ] = 0x00;
            data[ i++ ] = 0xFF;
            data[ i++ ] = 0xFF;
        }
    }

    unsigned
    twobyte( unsigned char low, unsigned char hi ) {
        return ( static_cast< unsigned >( hi ) << 8 ) + low;
    }
};

#endif // TGA_SURFACE_HH
