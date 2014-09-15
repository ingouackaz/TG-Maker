#include <cmath>
#include <iostream>
#include <QKeyEvent>

#include "MapEditorCanvas.hpp"
#include "Position.hpp"
#include "Image.hpp"
#include "MainWindow.hpp"

MapEditorCanvas::MapEditorCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
{

}

void MapEditorCanvas::OnInit()
{
    _view = new sf::View(sf::FloatRect(0, 0, 800, 608));

    _canvasEnabled = false;
    SetFramerateLimit(60);
    _zoomLvl = 0;
    _zoomUp = 0.8f;
    _zoomDown = 1.25f;
    _mapMode = REGULAR_MAP_MODE;
    _mouseIsPressed = false;
    updateScreenPos();


    _collisionTileImage.LoadFromFile("../resources/collision.png");

    _collisionTileSprite.SetImage(_collisionTileImage);
    _layerImage.LoadFromFile(LAYER_IMAGE_CALQUE);
    _layerSprite.SetImage(_layerImage);

    setFixedSize(800,608);
}

void MapEditorCanvas::OnUpdate()
{
    if (_canvasEnabled != true)
        return;
    SetView(*_view);
    eventHandler();
    updateScreenPos();
}



void    MapEditorCanvas::OnDraw()
{
    if (_canvasEnabled != true)
    {
        Clear(sf::Color(187,187,187));
        Display();
    }
    else
    {
        Clear();
        displayMap();
        // draw cursor
        drawCursor();
        Display();
    }
}

void    MapEditorCanvas::setCanvasEnabled(bool state)
{
    _canvasEnabled = state;
    setEnabled(state);
}

void MapEditorCanvas::mouseReleaseEvent( QMouseEvent * e )
{
    /* osef tout se passe dans mouse move event*/
    _mouseIsPressed = false;
    (void)e;
}

void MapEditorCanvas::mouseMoveEvent( QMouseEvent * e)
{
    if (_canvasEnabled == true)
    {
        int x = e->x() + (_view->GetCenter().x - 400);
        int y =  e->y() +(_view->GetCenter().y - 304);




        if (MainWindow::_tilesSelected.size() > 0 &&  x>= 0 && y >= 0 && y / 32 <= ProjectManagerBase::map_height && x / 32 <= ProjectManagerBase::map_width && _zoomLvl == 0 && _mapMode == REGULAR_MAP_MODE)
        {
            std::cout << "X [ " << x << " , Y "  << y << std::endl;
            if (_cursorMode == PEN_CURSOR_MODE)
                updateMap_PenModeColoring(x,y);
            else if (_cursorMode == RECT_CURSOR_MODE)
                updateMap_RectangleModeColoring(x,y);
            else if (_cursorMode == FILL_CURSOR_MODE)
                updateMap_FillModeColoring(x,y);
        }
    }
}

void MapEditorCanvas::mousePressEvent ( QMouseEvent * e )
{
    if (_canvasEnabled == true)
    {
        _mouseIsPressed = true;

        int x = e->x() + (_view->GetCenter().x - 400);
        int y =  e->y() +(_view->GetCenter().y - 304);



        if (MainWindow::_tilesSelected.size() &&  x>= 0 && y >= 0  && y / 32 <= ProjectManagerBase::map_height && x / 32 <= ProjectManagerBase::map_width && _zoomLvl == 0)
        {
            if (_mapMode == REGULAR_MAP_MODE)
            {

                if (_cursorMode == PEN_CURSOR_MODE)
                    updateMap_PenMode(x,y);
                else if (_cursorMode == RECT_CURSOR_MODE) {
                    updateMap_RectangleMode(x,y);
                }
                else if (_cursorMode == FILL_CURSOR_MODE) {
                    updateMap_FillMode();
                }
            }
            else
                collisionModeUpdate(x,y);
        }

    }
}

void  MapEditorCanvas::regularModeUpdate(int x, int y, int tilesetid)
{
    if (x >= 0 && y >= 0 && x / 32 < ProjectManagerBase::map_width && y / 32 < ProjectManagerBase::map_height)
    {
        PositionManager::singleton().getPosition((x / 32) , (y / 32) )->setTilesetId(MainWindow::_tilesSelected[tilesetid].second );
        PositionManager::singleton().getPosition((x / 32) , (y / 32) )->setTilesetX(MainWindow::_tilesSelected[tilesetid].first.first / 32);
        PositionManager::singleton().getPosition((x / 32) , (y / 32) )->setTilesetY(MainWindow::_tilesSelected[tilesetid].first.second / 32);
    }
}

void MapEditorCanvas::collisionModeUpdate(int x, int y)
{
    PositionManager::singleton().getPosition((x / 32) , (y / 32) )->setCollision(!(PositionManager::singleton().getPosition((x / 32) , (y / 32) )->getCollision()));
}

void MapEditorCanvas::setCursorMode(int mode)
{
    _cursorMode = mode;
}

void MapEditorCanvas::displayMap()
{
    for(int x = _topX - 1; x < _topX + 26 * pow(_zoomDown, _zoomLvl); ++x)
    {
        if (x >= 0 && x < ProjectManagerBase::map_width)
            for (int y = _topY - 1; y < _topY + 20 * pow(_zoomDown, _zoomLvl); ++y)
            {
                if (y >= 0 && y < ProjectManagerBase::map_height)
                {
                    regularModeDisplay(x,y);
                    if (_mapMode == COLLISION_MAP_MODE)
                        collisionModeDisplay(x,y);
                }
            }
    }
}

void MapEditorCanvas::updateMap_PenMode(int x, int y)
{
    regularModeUpdate(x, y,0);
}

void MapEditorCanvas::updateMap_RectangleMode(int x, int y)
{
    for (int i = x / 32; i < x / 32 + MainWindow::_tilesSelectedMapWidth; ++i)
    {
        for (int j = y / 32; j < y / 32 + MainWindow::_tilesSelectedMapHeight; ++j)
        {
            if (i < ProjectManagerBase::map_width && j < ProjectManagerBase::map_height
                    && i * 32 < _view->GetCenter().x + 400 && j * 32 < _view->GetCenter().y + 304)
            {
                PositionManager::singleton().getPosition(i, j)->setTilesetId(MainWindow::_tilesSelected[0].second );
                PositionManager::singleton().getPosition(i, j)->setTilesetX((MainWindow::_tilesSelected[0].first.first / 32 + i - x / 32));
                PositionManager::singleton().getPosition(i, j)->setTilesetY((MainWindow::_tilesSelected[0].first.second / 32 + j - y / 32));
            }
        }
    }
}

void MapEditorCanvas::updateMap_FillMode()
{
    int b = 0;
    for (int a = 0; a  < ProjectManagerBase::map_width * 32 ; ++a)
    {
        b = 0;
        while (b < ProjectManagerBase::map_height * 32)
        {
            regularModeUpdate(b, a,0);
            b++;
        }
    }
}

void MapEditorCanvas::updateMap_PenModeColoring(int x, int y)
{
    updateMap_PenMode(x,y);
    updateCursorPos(x,y);
}
void MapEditorCanvas::updateMap_RectangleModeColoring(int x, int y)
{
    (void)x;
    (void)y;
}
void MapEditorCanvas::updateMap_FillModeColoring(int x, int y)
{
    (void)x;
    (void)y;
}

void MapEditorCanvas::regularModeDisplay(int x, int y)
{
    _currentTileSprite.SetImage(*ImageManager::singleton()[PositionManager::singleton().getPosition(x, y)->getTilesetId()]);
    _currentTileSprite.SetSubRect(sf::IntRect(PositionManager::singleton().getPosition(x, y)->getTilesetX() * 32, PositionManager::singleton().getPosition(x, y)->getTilesetY() * 32, PositionManager::singleton().getPosition(x, y)->getTilesetX() * 32 + 32 , PositionManager::singleton().getPosition(x, y)->getTilesetY() * 32 + 32));
    _currentTileSprite.SetPosition(PositionManager::singleton().getPosition(x, y)->getMapY() * 32, PositionManager::singleton().getPosition(x, y)->getMapX() * 32);
    Draw(_currentTileSprite);
}

void MapEditorCanvas::collisionModeDisplay(int x, int y)
{
    if ( PositionManager::singleton().getPosition(x, y)->getCollision() == true)
    {
        _collisionTileSprite.SetPosition(PositionManager::singleton().getPosition(x, y)->getMapY() * 32, PositionManager::singleton().getPosition(x, y)->getMapX() * 32);
        _collisionTileSprite.SetColor(sf::Color(255,255,255,128));
        Draw(_collisionTileSprite);
    }
}

void MapEditorCanvas::wheelEvent(QWheelEvent* e)
{
    if (e->delta() > 0)
    {
        if (_zoomLvl > 0)
        {
            _zoomLvl--;
            _view->Zoom(_zoomDown);
            if (_zoomLvl == 0)
            {
                _view->Move(-((int)(_view->GetCenter().x - 400) % 32), -((int)(_view->GetCenter().y - 304) % 32));
            }
        }
    }
    else
    {
        if (_zoomLvl < 2)
        {

            _zoomLvl++;
            _view->Zoom(_zoomUp);
        }
    }
}

void    MapEditorCanvas::keyPressEvent(QKeyEvent *k)
{
    (void)k;
}

void    MapEditorCanvas::eventHandler()
{
    sf::Event Event;

    // Ajouter une limite
    while (GetEvent(Event))
    {
        // Escape key pressed
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::W))
            _view->Move( 0,     -32 * pow(_zoomUp, _zoomLvl));
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S))
            _view->Move( 0,      32 * pow(_zoomUp, _zoomLvl));
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A))
            _view->Move( -32 * pow(_zoomUp, _zoomLvl),      0);
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D))
            _view->Move( 32 * pow(_zoomUp, _zoomLvl),      0);
        if (Event.Type == sf::Event::MouseMoved)
            updateCursorPos(Event.MouseMove.X,Event.MouseMove.Y );
    }
}


void    MapEditorCanvas::updateScreenPos()
{
    _topX = (_view->GetCenter().x - 400 * pow(_zoomDown, _zoomLvl)) / 32;
    _topY = (_view->GetCenter().y - 304 * pow(_zoomDown, _zoomLvl)) / 32;
}


void    MapEditorCanvas::setMapMode(int mode)
{
    _mapMode = mode;
}


void    MapEditorCanvas::drawCursor()
{
    if (_zoomLvl == 0)
        Draw(_layerSprite);
}

void    MapEditorCanvas::drawPenCursor()
{

}

void MapEditorCanvas::updateCursorPos(int x,int y)
{
    _layerSprite.SetX(((x/ 32) * 32) + (_view->GetCenter().x - 400));
    _layerSprite.SetY(((y / 32) * 32) + (_view->GetCenter().y - 304));
}
