#ifndef LAYER_HH
#define LAYER_HH

class Layer {
    
public:
    Layer( int sx, int sy );
    ~Layer();

    int sizeX() const;
    int sizeY() const;
    int size() const;

protected:
    int _sx, _sy;

    int index( int x, int y ) const;
};

#endif // LAYER_HH
