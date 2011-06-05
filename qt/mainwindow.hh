#ifndef MAIN_WINDOW_HH
#define MAIN_WINDOW_HH

#include "../worldmap.hh"

#include <QGLWidget>
#include <QKeyEvent>
#include <QTimer>

class MainWindow : public QGLWidget {
    Q_OBJECT

public:
    MainWindow( QWidget *parent );
    ~MainWindow();

    void setWorldMap( WorldMap * wm );

    void initializeGL();
    void resizeGL( int w, int h );
    void updateGL();

    void keyPressEvent( QKeyEvent *e );

    void drawWorldMap();
    void drawCities();
    void drawCity( City *c );
    void drawTile( float r, float g, float b );
    void drawShip();
    void drawControlPanel();

private:
    WorldMap * _wm;
    QTimer * _timer;

    float xpan, ypan;
};

#endif // MAIN_WINDOW_HH
