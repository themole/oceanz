#include "mainwindow.hh"

#include <cmath>

MainWindow::MainWindow( QWidget *parent )
    : QGLWidget( parent ) {
    _timer = new QTimer();
    _wm = new WorldMap( 1024, 1024 );

    this->setAttribute( Qt::WA_QuitOnClose, true );
    xpan = ypan = 0;
}

MainWindow::~MainWindow() {
    if( _wm != 0 )
        delete _wm;
    delete _timer;
}

void
MainWindow::setWorldMap( WorldMap * map ) {
    if( _wm != 0 )
        delete _wm;
    _wm = map;
}

void
MainWindow::initializeGL() {
    glClear( GL_COLOR_BUFFER_BIT );
}

#ifndef PI
#define PI 3.14159265358979323846f
#endif

void
MainWindow::resizeGL( int w, int h ) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0., w, h, 0., 0., 10. );
    updateGL();
}

void
MainWindow::updateGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    float rad = 10;
    glTranslatef( -xpan * 2 * rad * cos( PI / 6 ) + ypan* rad * cos( PI/6 ),
                  -ypan * ( rad + rad * sin( PI/6 ) ),
                  0 );
    drawWorldMap();
    swapBuffers();
}

void
MainWindow::drawWorldMap() {
    float rad = 10;
    glPushMatrix();
        glTranslatef( rad * cos( PI/6 ),
                      rad,
                      0.f );
        //int xp = xpan; // int yp = ypan;
        for( int y = ypan-1; y < ypan + 90; y++ ) {
            for( int x = xpan; x < xpan + 200; x++ ) {
                if( x < 0 || x >= _wm->sizeX() ||
                    y < 0 || y >= _wm->sizeY() )
                    continue;

                glPushMatrix();
                glTranslatef( ( 2*x - y ) * rad * cos( PI/ 6 ),
                              y * ( rad + rad * sin( PI/6 ) ),
                              0.f);
                if( _wm->region( x, y ) == WATER )
                    drawTile( 0.f, 0.f, 1.f + _wm->height( x, y )/255.f );
                else if( _wm->region( x, y ) == LAND )
                    drawTile( 0.f, 1.f - _wm->height( x, y )/255.f, 0.f );
                else {
                    drawTile( 1.f, 0.f, 0.f );
                }
                glPopMatrix();
            }
        }
//        drawCities();
    glPopMatrix();
}

void
MainWindow::drawCities() {
    float rad = 10;
    for( auto it  = _wm->cityLayer()->cities().begin();
              it != _wm->cityLayer()->cities().end();
              it++ ) {

        glPushMatrix();

        glTranslatef( ( 2*it->second.x() - it->second.y() ) * rad * cos( PI/ 6 ),
                      it->second.y() * ( rad + rad * sin( PI/6 ) ),
                      0.f);
        drawCity( it->first );

        glPopMatrix();
    }
}

void
MainWindow::drawCity( City* c ) {
    float rad = 10.f;
    std::list< Position > list = c->positions();
    for( auto it  = list.begin(); it != list.end(); it++ ) {
        glTranslatef( ( 2*it->x() - it->y() ) * rad * cos( PI/ 6 ),
                      it->y() * ( rad + rad * sin( PI/6 ) ),
                      0.f);
        drawTile( 1.f, 1.f, 0.f );
    }
}

void
MainWindow::drawTile( float r, float g, float b ) {
    float rad = 10.f;
    glColor3f( r, g, b );
    glBegin( GL_POLYGON );
        for( int k = 0; k < 6; k++ )
        glVertex2f( rad*cos( PI/6 + k*PI/3 ),
                    rad*sin( PI/6 + k*PI/3 ) );
    glEnd();
}

void
MainWindow::drawShip() {
}

void
MainWindow::drawControlPanel() {
}

void
MainWindow::keyPressEvent( QKeyEvent *e ) {
    switch( e->key() ) {
        case Qt::Key_Escape:
            this->close();
            break;
        case Qt::Key_U:
            this->updateGL();
            break;
        case Qt::Key_Right:
            xpan += 4;
            updateGL();
            break;
        case Qt::Key_Left:
            xpan -= 4;
            updateGL();
            break;
        case Qt::Key_Up:
            ypan -= 4;
            xpan -= 2;
            updateGL();
            break;
        case Qt::Key_Down:
            ypan += 4;
            xpan += 2;
            updateGL();
            break;
    }
}
