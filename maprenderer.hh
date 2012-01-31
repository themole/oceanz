#ifndef MAPRENDERER
#define MAPRENDERER

#include "worldmap.hh"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif
#include <GL/gl.h>
#include <GL/glext.h>

#include <ostream>
#include <string>

// renders a WorldMap object to a given screen
// creates a vertex buffer object representing the map
// each hex is conveted into 7 vertices
// ( one in the middle and 6 for the corners )
// no vertex is created twice

class MapRenderer {

private:
    static unsigned char const VERTICES_PER_HEXAGON;
    static GLfloat const SMALLEST_UNIT;


public:
    struct vertex {
        GLfloat x, y, z;
        GLfloat r, g, b;

        vertex()
            : x( 0.f ), y( 0.f ), z( 0.f ),
              r( 1.f ), g( 1.f ), b( 1.f ) {}

        // no validation here
        vertex( GLfloat xx, GLfloat yy, GLfloat zz,
                GLfloat rr, GLfloat gg, GLfloat bb )
            : x( xx ), y( yy ), z( zz ),
              r( rr ), g( gg ), b( bb ) {
        }
        friend std::ostream & operator<<( std::ostream &, vertex const & );
    };

public: // functions
    MapRenderer( WorldMap const & wm );
    ~MapRenderer();

    void render();
    void printVertices() const;

private: // functions
    void initBufferObjects();
    void createVertices();
    void createVerticesComplex();

private:
    WorldMap const & _wm;

    vertex   *_vs;
    GLushort *_is;

    // vertex and element/index buffer object handles
    GLuint _vbo, _ibo;
};

#endif // MAPRENDERER
