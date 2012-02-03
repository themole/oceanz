#ifndef MAIN_WINDOW_HH
#define MAIN_WINDOW_HH

#include "../position.hh"
#include "../worldmap.hh"
#include "../surface.hh"
#include "../citycontrol.hh"

#include <QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

class MainWindow : public QGLWidget {
    Q_OBJECT

public:
    MainWindow( QWidget *parent );
    ~MainWindow();

    QSize sizeHint();

    void setWorldMap( WorldMap * wm );

    void initializeGL();
    void resizeGL( int w, int h );
    void updateGL();

    void keyPressEvent( QKeyEvent *e );
    void mouseMoveEvent( QMouseEvent *e );

    void drawWorldMap();
    void drawCities();
    void drawCity( City *c );
    void drawTile( float r, float g, float b );
    void drawShip();
    void drawControlPanel();

    Position const & mouseTile( int mx, int my ) const;

public slots:
    void upgradeRandomCity();
    void printMousePosition();

private:
    WorldMap * _wm;
    QTimer * _timer;

    CityControl * _cc;

    int xpan, ypan;

    GLuint screen_texture;

    Surface* screen_surface;
    Surface* land_sprite;
    Surface* water_sprite;
    Surface* city_sprite;
    Surface* city_sprite_max_level;
    Surface* around_city_sprite;
    Surface* around_city_water_sprite;

};

#endif // MAIN_WINDOW_HH
