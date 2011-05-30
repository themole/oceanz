#ifndef LAYER_HH
#define LAYER_HH

#include "position.hh"

template< typename T >
class Layer {

public:
    typedef T value_type;

public:
    Layer( unsigned sx, unsigned sy );
    virtual ~Layer();

    unsigned sizeX() const;
    unsigned sizeY() const;

    virtual value_type const & operator()( unsigned i ) = 0;
    virtual value_type const & operator()( unsigned x, unsigned y ) = 0;
    virtual value_type const & operator()( Position const & p ) = 0;

    virtual void operator()( unsigned i, value_type const & ) = 0;
    virtual void operator()( unsigned x, unsigned y, value_type const & ) = 0;
    virtual void operator()( Position const & p, value_type const & ) = 0;

    virtual bool valid() const = 0;

protected:
    unsigned _sx, _sy;

    unsigned index( unsigned x, unsigned y ) const;
    unsigned index( Position const & ) const;

    Position position( unsigned i ) const;

    // not allowed
    Layer(); 
    Layer( Layer const & );
    Layer & operator=( Layer const & );
};

// implementation
template< typename T >
Layer< T >::Layer( unsigned sx, unsigned sy )
    : _sx( sx ), _sy( sy ) {
    if( _sx == 0 ) _sx = 1;
    if( _sy == 0 ) _sy = 1;
}

template< typename T >
Layer< T >::~Layer() {}

template< typename T >
unsigned 
Layer< T >::sizeX() const {
    return _sx;
}

template< typename T >
unsigned 
Layer< T >::sizeY() const {
    return _sy;
}

template< typename T >
unsigned
Layer< T >::index( unsigned x, unsigned y ) const {
    return ( x%_sx ) + _sx *( y%_sy );
}

template< typename T >
unsigned
Layer< T >::index( Position const & p ) const {
    return index( p.x(), p.y() );
}

template< typename T >
Position
Layer< T >::position( unsigned i ) const {
    return Position( i%_sx, i/_sy );
}

#endif // layer
