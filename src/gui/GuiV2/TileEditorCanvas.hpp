#ifndef TILEEDITORCANVAS_HPP
#define TILEEDITORCANVAS_HPP

#include <iostream>
#include <string>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "QSFMLCanvas.hpp"
#include <Qt/qapplication.h>
#include <Qt/qframe.h>
#include <Qt/qlabel.h>
#include <Qt/qevent.h>
#include <map>

#include "RectSelection.hpp"

#define SCALE_CURSOR_ICON 10

#define TILE_EDITOR_SCREEN_WIDTH 256
#define TILE_EDITOR_SCREEN_HEIGHT 544

#define LAYER_IMAGE_CALQUE "../resources/frameCalque.png"



typedef  std::pair< std::pair<int, int> , std::string >   TileInfo;

class TileEditorCanvas: public QSFMLCanvas
{
public :
    TileEditorCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size);

    // Fonctions publiques
public :
    virtual void    setCanvasEnabled(bool);
    void            setCursorMode(int mode);
    void            initAllTileSet();
    void            updateTileSet(int index);
private :
    // Fonctions de gestion de la souris
    void mouseReleaseEvent ( QMouseEvent * e );
    void mousePressEvent ( QMouseEvent * e );
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent* e);

    void        drawCursor();
    void        drawPenCursor();
    void        drawRectCursor();
    void        drawFillCursor();
    void        setSelectedTile(int x, int y);
    void        setSelectedTiles();


    // Fonctions lib Qt virtuel
    virtual void OnInit();
    virtual void OnUpdate();
    virtual void OnDraw();

    // Attributs
    sf::Image  _frameImage;  ///< Some image to show
    sf::Sprite _frameSprite; ///< A sprite to display the image
    sf::Image  _selectedImage;
    sf::Sprite _selectedSprite;
    sf::Image  _layerImage;
    sf::Sprite _layerSprite;
    sf::Image  _tilesetImage;
    sf::Sprite _tilesetSprite;

    sf::Sprite _currentTilesetSprite;

    //      Stocker les pointeurs sur les TileSet
    bool  _canvasEnabled;
    bool   _mouseIsPressed;
    int   _cursorMode;
    int   _currentTileSetId;
    std::pair<int,int>  _beginRectCoo;
    std::pair<int,int>  _endRectCoo;

};

#endif // TILEEDITORCANVAS_HPP
