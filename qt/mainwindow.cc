#include "mainwindow.hh"

#include "tgafile.hh"
#include "citycontrol.hh"
#include <string>

#include <cmath>


MainWindow::MainWindow( QWidget *parent )
    : QGLWidget( parent ) {

    _wm = 0;
    _cc = 0;

    _timer = new QTimer();
    QObject::connect( _timer, SIGNAL( timeout() ), this, SLOT( upgradeRandomCity() ) );

    this->setAttribute( Qt::WA_QuitOnClose, true );
    xpan = ypan = 32;
    screen_surface = 0;

    this->setMinimumSize( sizeHint() );
    this->setMouseTracking( true );
}

MainWindow::~MainWindow() {
    if( _wm )
        delete _wm;
    if( _cc )
        delete _cc;

    _timer->stop();
    delete _timer;

    delete land_sprite;
    delete water_sprite;
}

QSize MainWindow::sizeHint() {
    return QSize( 800, 600 );
}

void
MainWindow::setWorldMap( WorldMap * map ) {
    if( _wm ) delete _wm;
    if( _cc ) delete _cc;
    _wm = map;
    _cc = new CityControl( _wm );
}

void
MainWindow::initializeGL() {
    // SET UP for SHADERS goes HERE

    // SET UP for SCREEN TEXTURE is HERE:
    glGenTextures( 1, &screen_texture );
    glBindTexture( GL_TEXTURE_2D, screen_texture );
    glTexEnvi( GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glEnable( GL_TEXTURE_2D );
    // glEnable( GL_BLEND );
    // glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // THIS SPRITE IS TEMPORARY:
//    TGAFile land_tga( "tileframes/land_00.tga" );
//    TGAFile water_tga( "tileframes/water_00.tga" );

//    land_sprite = new Surface( land_tga );
//    water_sprite = new Surface( water_tga );

    // try stb_image lib
    land_sprite = new Surface( "tileframes/land_00.tga" );
    water_sprite = new Surface( "tileframes/water_00.tga" );
    city_sprite = new Surface( "tileframes/city_00.tga" );
    city_sprite_max_level = new Surface( "tileframes/city_01.tga" );
    around_city_sprite = new Surface( "tileframes/around_city.tga" );
    around_city_water_sprite = new Surface( "tileframes/around_city_water.tga" );
}

#ifndef PI
#define PI static_cast< float >( M_PI )
#endif

void
MainWindow::resizeGL( int w, int h ) {
    // Re-create surface:
    delete screen_surface;
    screen_surface = new Surface( w, h );
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0., w, h, 0., 0., 10. );
    updateGL();
}

#define GL_BGRA 0x80E1

void
MainWindow::updateGL() {
//    glClearColor( 0.f, 0.f, 0.f, 1.f );
//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // glTranslatef( -xpan * 2 * rad * cos( PI / 6 ) + ypan* rad * cos( PI/6 ),
    //               -ypan * ( rad + rad * sin( PI/6 ) ),
    //               0 );
    screen_surface->clear( 0, 0, 0, 0xFF );
    drawWorldMap();

    // THIS is the FULLSCREEN QUAD:
    glBindTexture( GL_TEXTURE_2D, screen_texture );

    glTexImage2D( GL_TEXTURE_2D, 0,
                  GL_RGBA,
                  width(), height(), 0,
                  GL_RGBA,
                  GL_UNSIGNED_BYTE,
                  *screen_surface );
    glBegin( GL_QUADS );
    glTexCoord2i( 0, 0 ); glVertex2i( 0, 0 );
    glTexCoord2i( 0, 1 ); glVertex2i( 0, height() );
    glTexCoord2i( 1, 1 ); glVertex2i( width(), height() );
    glTexCoord2i( 1, 0 ); glVertex2i( width(), 0 );
    glEnd();
    swapBuffers();
}

void
MainWindow::drawWorldMap() {
    for( int x = xpan - 1 - width()/32 - height()/60;
         x < xpan + 1 + width()/32 + height()/60; ++x ) {
        for( int y = ypan - 1 - height()/30; y < ypan + 2 + height()/30; ++y ) {

            if( x < 0 || y < 0 || x >= _wm->sizeX() || y >= _wm->sizeY() )
                continue;

            int xa = 8*( 2*( x - xpan ) - ( y - ypan ) ) + width()/2 - 8;
            int ya = 15*( y - ypan ) + height()/2 - 7;

            if( _wm->region( x, y )->is( LAND ) ) {
                if( _wm->cityLayer()->insideCity( x, y ) != 0 ) {
                    if( _wm->cityLayer()->city( x, y )->maxLevel() ) 
                        screen_surface->paint( *city_sprite_max_level, xa, ya );
                    else
                        screen_surface->paint( *city_sprite, xa, ya );
                } else if ( _wm->cityLayer()->aroundCity( x, y ) ) { 
                    screen_surface->paint( *around_city_sprite, xa, ya );
                } else
                screen_surface->paint( *land_sprite, xa, ya );
            }
            else if( _wm->cityLayer()->aroundCity( x, y ) )
                screen_surface->paint( *around_city_water_sprite, xa, ya );
            else
                screen_surface->paint( *water_sprite, xa, ya );
        }
    }            
}

void
MainWindow::drawCities() {
//    float rad = 10;
//    for( auto it  = _wm->cityLayer()->cities().begin();
//              it != _wm->cityLayer()->cities().end();
//              it++ ) {
//
//        glPushMatrix();
//
//        glTranslatef( ( 2*it->second.x() - it->second.y() ) * rad * cos( PI/ 6 ),
//                      it->second.y() * ( rad + rad * sin( PI/6 ) ),
//                      0.f);
//        drawCity( it->first );
//
//        glPopMatrix();
//    }
}

void
MainWindow::drawCity( City* c ) {
    c = c;
//    float rad = 10.f;
//    std::list< Position > list = c->positions();
//    for( auto it  = list.begin(); it != list.end(); it++ ) {
//        glTranslatef( ( 2*it->x() - it->y() ) * rad * cos( PI/ 6 ),
//                      it->y() * ( rad + rad * sin( PI/6 ) ),
//                      0.f);
//        drawTile( 1.f, 1.f, 0.f );
//    }
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
            upgradeRandomCity();
            break;
        case Qt::Key_L:
        case Qt::Key_Right:
            xpan += 4;
            updateGL();
            break;
        case Qt::Key_H:
        case Qt::Key_Left:
            xpan -= 4;
            updateGL();
            break;
        case Qt::Key_K:
        case Qt::Key_Up:
            ypan -= 4;
            xpan -= 2;
            updateGL();
            break;
        case Qt::Key_J:
        case Qt::Key_Down:
            ypan += 4;
            xpan += 2;
            updateGL();
            break;
        case Qt::Key_Space:
            if( _timer->isActive() )
                _timer->stop();
            else
                _timer->start(150);
            break;
    }
}

void
MainWindow::mouseMoveEvent( QMouseEvent *e ) {
    std::cout << "Mouse: ( " << e->x() << ", " << e->y() << " ), ";
    std::cout << "left_btn: ";
    if( e->buttons() & Qt::LeftButton ) std::cout << "yes";
    else    std::cout << "no";
    std::cout << ", right_btn: ";
    if( e->buttons() & Qt::RightButton ) std::cout << "yes";
    else    std::cout << "no";
    std::cout << std::endl;
}

void
MainWindow::upgradeRandomCity() {
    if( _cc )
        _cc->upgradeCity( ( rand() % _wm->cityLayer()->cities().size() ) + 1 );

    bool done = true;
    for( auto cit = _wm->cityLayer()->cities().begin();
              cit != _wm->cityLayer()->cities().end();
              cit++ ) {
        if( !cit->second->maxLevel() )
            done = false;
    }
    if( done ) 
        _timer->stop();
    updateGL();
}

void
MainWindow::printMousePosition() {
    if( this->isActiveWindow() ) {
        QPoint p = this->mapFromGlobal(QCursor::pos());
        std::cout << "mouse position " << p.x() << ", " << p.y() << std::endl;
    }
}

