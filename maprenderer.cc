#include "maprenderer.hh"

#define BUFFER_OFFSET( i ) ( ( char* ) NULL + ( i ) )

unsigned char const MapRenderer::VERTICES_PER_HEXAGON = 7;
GLfloat const MapRenderer::SMALLEST_UNIT = 0.25f;

MapRenderer::MapRenderer( WorldMap const & wm )
    : _wm( wm ) {

    createVertices(); 
    initBufferObjects();
}

MapRenderer::~MapRenderer() {
    glDeleteBuffers( 1, &_vbo );
    glDeleteBuffers( 1, &_ibo );

    delete[] _vs;
    delete[] _is;
}

void
MapRenderer::render() {
    glDrawArrays( GL_TRIANGLES, 0, 6 * ( _wm.sizeX()-1 ) * ( _wm.sizeY()-1 ) );
}

void
MapRenderer::initBufferObjects() {

    GLuint vertex_cnt = 0;

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    glGenBuffers( 1, &_vbo );
    glGenBuffers( 1, &_ibo );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER,
                  sizeof( MapRenderer::vertex ) * vertex_cnt,
                  _vs,
                  GL_STATIC_DRAW );

    glVertexPointer( 2, GL_FLOAT, sizeof( MapRenderer::vertex ), &_vs[ 0 ].x );
    glColorPointer( 3, GL_FLOAT, sizeof( MapRenderer::vertex ), &_vs[ 0 ].r );
        
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                  sizeof( GLushort ) * vertex_cnt,
                  _is,
                  GL_STATIC_DRAW );
}

// creates one vertex per hex
void
MapRenderer::createVertices() {
    if( _vs )
        delete[] _vs;
    if( _is )
        delete[] _is;

    // exactly one vertex per hex
    GLuint vertex_cnt = _wm.sizeX() * _wm.sizeY();
    // amount of resulting triangles
    GLuint triangle_cnt = 2 * ( _wm.sizeX()-1 ) * ( _wm.sizeY()-1 );

    // create arrays
    _vs = new vertex[ vertex_cnt ];
    _is = new GLushort[ 3 * triangle_cnt ]; // drawing each triangle individually

    // filling vertex array
    // row major
    for( int y = 0 ; y < _wm.sizeY(); y++ )
        for( int x = 0; x < _wm.sizeX(); x++ ) {
            _vs[ x + _wm.sizeX()*y ] = vertex( ( _wm.sizeY() * 7.f + ( 14.f * x - 7.f * y ) ) / ( 14.f * _wm.sizeX() + 7.f * _wm.sizeY() ),
                                               ( (float)y ) / _wm.sizeY(), 
                                               0.f,
                                               1.f - ( float )x/(float)_wm.sizeX(), 1.f - ( float )y/(float)_wm.sizeY(), 1.f );

            // put 6 index entries into _is forming the SE and S triangles
            // last line does not have those triangles
            if( x == _wm.sizeX() - 1 || y == _wm.sizeY() - 1 ) continue;
            
            // S triangle:
            unsigned i = x + _wm.sizeX() * y;
            _is[ 6 * i     ] = i;  
            _is[ 6 * i + 1 ] = i + _wm.sizeX();
            _is[ 6 * i + 2 ] = i + _wm.sizeX() + 1; 
            _is[ 6 * i + 3 ] = i;
            _is[ 6 * i + 4 ] = i + _wm.sizeX() + 1;
            _is[ 6 * i + 5 ] = i + 1; 
        }
}

void
MapRenderer::createVerticesComplex() {
    // calculate amount of vertices the whole map has
    GLuint vertex_cnt = _wm.sizeY() * ( 3 * _wm.sizeX() + 1 ) + 2 * _wm.sizeX() + 1;
    // calculate amount of bytes needed to store vertex information
//    GLuint sizeInBytes = sizeof( MapRenderer::vertex ) * vertex_cnt;

    _vs = new vertex[ vertex_cnt ];
    _is = new GLushort[ vertex_cnt * VERTICES_PER_HEXAGON ];

    unsigned magic_number = _wm.sizeY() * ( 3 * _wm.sizeX() + 1 );

    // vertex array
    for( unsigned i = 0; i < vertex_cnt; i++ ) {

        int row = i / magic_number;
        float ycorrection = row * 12;   // in smalles units
        float xcorrection = -7 * row;   // in smalles units
        int ii = i - row * ( _wm.sizeY() * ( 3*_wm.sizeX() + 1 ) );

        if( ii < _wm.sizeX() ) {
            _vs[ i ] = vertex( SMALLEST_UNIT * ( xcorrection + 7 + 14 * ii ),
                               SMALLEST_UNIT * ( ycorrection ),
                               0.f,
                               1.f, 1.f, 1.f );
        }
        else if( ii - _wm.sizeX() < _wm.sizeX() + 1 ) {
            _vs[ i ] = vertex( SMALLEST_UNIT * ( xcorrection + 14 * ii ),
                               SMALLEST_UNIT * ( ycorrection + 4 + 8*row ),
                               0.f,
                               1.f, 1.f, 1.f );
        }
        else if( i < magic_number ) {
            _vs[ i ] = vertex( SMALLEST_UNIT * ( xcorrection + 7 + 14 * ii ),
                               SMALLEST_UNIT * ( ycorrection + 8 + 8*row ),
                               0.f,
                               1.f, 1.f, 1.f );
        }
        else if( i >= magic_number ) {
            int ii = i - magic_number;
            if( i < magic_number + _wm.sizeX() + 1 ) {
                _vs[ i ] = vertex( SMALLEST_UNIT * ( xcorrection + 7 + 14 * ii ),
                                   SMALLEST_UNIT * ( ycorrection ),
                                   0.f,
                                   1.f, 1.f, 1.f );
            }
            else {
                _vs[ i ] = vertex( SMALLEST_UNIT * ( xcorrection + 14 * ( ii + 1 ) ),
                                   SMALLEST_UNIT * ( ycorrection + 4 + 8 * row ),
                                   0.f,
                                   1.f, 1.f, 1.f );
            }
        }
    }
}
