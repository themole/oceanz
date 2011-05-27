#ifndef LAYER_HH
#define LAYER_HH

class Layer {

public:
    Layer( unsigned width, unsigned height );
    virtual ~Layer();

    unsigned sizeX() const;
    unsigned sizeY() const;

    virtual bool isInitialized() const = 0;

protected:
    unsigned _sx, _sy;

    unsigned index( unsigned x, unsigned y ) const;
    Layer(); 
};

#endif // layer
