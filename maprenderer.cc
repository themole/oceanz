#include "maprenderer.hh"

#define BUFFER_OFFSET( i ) ( ( char* ) NULL + ( i ) )

unsigned char const MapRenderer::VERTICES_PER_HEXAGON = 7;
GLfloat const MapRenderer::SMALLEST_UNIT = 0.25f;

std::ostream &
operator<<( std::ostream & os, MapRenderer::vertex const & v ) {
    os << "( " << v.x << ", " << v.y << ", " << v.z << " )";
    return os;
}

MapRenderer::MapRenderer( WorldMap const & wm )
    : _wm( wm ), _vs( 0 ), _is( 0 ) {

    createVertices(); 
    initBufferObjects();
}

MapRenderer::~MapRenderer() {
    uninitBufferObjects();

    if( _vs != 0 )
        delete[] _vs;
//    if( _is != 0 )
//        delete[] _is;
}

void
MapRenderer::render() {
    glClear( GL_COLOR_BUFFER_BIT );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    glVertexPointer( 3,                             // components
                     GL_FLOAT,                      // type
                     sizeof( MapRenderer::vertex ), // stride
                     &_vs[ 0 ].x );                 // offset
    glColorPointer(  3,
                     GL_FLOAT,
                     sizeof( MapRenderer::vertex ),
                     &_vs[ 0 ].r );

    // draw
    glDrawArrays( GL_TRIANGLES, /*first*/ 0, /*count*/ 3*_tcnt);

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
}

void
MapRenderer::initBufferObjects() {

    if( _vcnt == 0 || _tcnt == 0 )
        return;

    glGenBuffers( 1, &_vbo );
//    glGenBuffers( 1, &_ibo );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER,
                  sizeof( MapRenderer::vertex ) * _vcnt,
                  _vs,
                  GL_STATIC_DRAW );

//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
//    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
//                  sizeof( GLushort ) * vertex_cnt,
//                  _is,
//                  GL_STATIC_DRAW );
}

void
MapRenderer::uninitBufferObjects() {
    glDeleteBuffers( 1, &_vbo );
//    glDeleteBuffers( 1, &_ibo );
}

// creates one vertex per hex
void
MapRenderer::createVertices() {
    if( _vs || _is )
        return;

    // exactly one vertex per hex
    _vcnt = _wm.sizeX() * _wm.sizeY();
    // amount of resulting triangles
    _tcnt = 2 * ( _wm.sizeX()-1 ) * ( _wm.sizeY()-1 );

    // create arrays
    _vs = new vertex[ _vcnt ];
//    _is = new GLushort[ 3 * _tcnt]; // drawing each triangle individually

    // filling vertex array
    // row major
    for( int y = 0 ; y < _wm.sizeY(); y++ )
        for( int x = 0; x < _wm.sizeX(); x++ ) {
            _vs[ x + _wm.sizeX()*y ] = vertex( ( _wm.sizeY() * 7.f + ( 14.f * x - 7.f * y ) ) / ( 14.f * _wm.sizeX() + 7.f * _wm.sizeY() ),
                                               ( (float)y ) / _wm.sizeY(), 
                                               0.f,
                                               1.f - ( float )x/(float)_wm.sizeX(), 1.f - ( float )y/(float)_wm.sizeY(), 1.f );

 //           // put 6 index entries into _is forming the SE and S triangles
 //           // last line does not have those triangles
 //           if( x == _wm.sizeX() - 1 || y == _wm.sizeY() - 1 ) continue;
 //           
 //           // S triangle:
 //           unsigned i = x + _wm.sizeX() * y;
 //           _is[ 6 * i     ] = i;  
 //           _is[ 6 * i + 1 ] = i + _wm.sizeX();
 //           _is[ 6 * i + 2 ] = i + _wm.sizeX() + 1; 
 //           _is[ 6 * i + 3 ] = i;
 //           _is[ 6 * i + 4 ] = i + _wm.sizeX() + 1;
 //           _is[ 6 * i + 5 ] = i + 1; 
        }
}

void
MapRenderer::printVertices() const {
    if( !_vs ) {
        std::cout << "vertices not generated yet." << std::endl;
        return;
    }
    std::cout << "vertices:" << std::endl;
    for( int i = 0; i < _wm.sizeX() * _wm.sizeY(); i++ ) 
        std::cout << _vs[i] << std::endl;

}
