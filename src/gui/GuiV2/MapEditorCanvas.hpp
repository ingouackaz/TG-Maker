#ifndef MAPEDITORCANVAS_HPP
#define MAPEDITORCANVAS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "QSFMLCanvas.hpp"
#include <Qt/qapplication.h>
#include <Qt/qframe.h>
#include <Qt/qlabel.h>
#include <Qt/qevent.h>

#include "RectSelection.hpp"


// 26 Tile en largeur  sur 18 Tile en hauteur
#define MAP_EDITOR_SCREEN_WIDTH 832
#define MAP_EDITOR_SCREEN_HEIGHT 576
#define MAP_WIDTH  2000
#define MAP_HEIGHT 2000
#define REGULAR_MAP_MODE 0
#define COLLISION_MAP_MODE 1
#define LAYER_IMAGE_CALQUE "../resources/frameCalque.png"

class MapEditorCanvas: public QSFMLCanvas
{
public :
    MapEditorCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size);
    virtual void    setCanvasEnabled(bool);

    void setMapMode(int);
    void setCursorMode(int mode);

private :
    // Fonctions de gestion de la souris


    void mouseReleaseEvent ( QMouseEvent * e );
    void mousePressEvent ( QMouseEvent * e );
    void mouseMoveEvent( QMouseEvent * e);
    void wheelEvent(QWheelEvent* e);

    // Clavier
    void    keyPressEvent( QKeyEvent *k );
    void  eventHandler();

    virtual void OnInit();
    virtual void OnUpdate();
    virtual void OnDraw();

    // draw - display
    void display();
    void displayRectangle();
    void displayImage();
    void displayMap();
    void drawCursor();
    void drawPenCursor();
    void drawFillCursor();

    // update
    void updateScreenPos();
    void updateCursorPos(int x,int y);
    void updateMap_PenMode(int x, int y);
    void updateMap_RectangleMode(int x, int y);
    void updateMap_FillMode();
    void updateMap_PenModeColoring(int x, int y);
    void updateMap_RectangleModeColoring(int x, int y);
    void updateMap_FillModeColoring(int x, int y);


    void regularModeUpdate(int x, int y, int tilesetid);
    void regularModeDisplay(int x, int y);
    void collisionModeUpdate(int x, int y);
    void collisionModeDisplay(int x, int y);

    // attributs
    std::pair<mapCase, std::string>     **_map;
    sf::View                        *_view;
    bool                                _canvasEnabled;
    bool                                _isValidPos;
    bool                              _mouseIsPressed;
    sf::Sprite                       _layerSprite;
    sf::Image                       _layerImage;
    sf::Image                       _currentTileImage;
    sf::Sprite                      _currentTileSprite;
    sf::Image                       _collisionTileImage;
    sf::Sprite                      _collisionTileSprite;
    int                             _cursorMode;
    int                           _zoomLvl;
    int                            _theX;
    int                            _theY;
    int                            _topX;
    int                            _topY;
    int                            _mapMode;
    float                          _zoomUp;
    float                          _zoomDown;
};

#endif // MAPEDITORCANVAS_HPP
