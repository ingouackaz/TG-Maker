#include "TileEditorCanvas.hpp"
#include <iostream>

#include "Image.hpp"
#include "MainWindow.hpp"

TileEditorCanvas::TileEditorCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, QPoint(0,0), Size) ,_cursorMode(PEN_CURSOR_MODE)
{
    (void)Position;

    // set defaultTileSet
}

void            TileEditorCanvas::initAllTileSet()
{
    sf::Image *img =     ImageManager::singleton().getByRank(0);
    _currentTilesetSprite.SetImage(*img);
}

void TileEditorCanvas::OnInit()
{
    _canvasEnabled = false;
    SetFramerateLimit(20);
    _cursorMode = 0;
    _currentTileSetId = 0;
    // Liste des curseurs
    _frameImage.LoadFromFile("../resources/selected.png");
    _frameSprite.SetImage(_frameImage);

    // Le calque
    _layerImage.LoadFromFile("../resources/frameCalque.png");
    _layerSprite.SetImage(_layerImage);
    setSelectedTile(0,0);

    _beginRectCoo.first = 0;
    _beginRectCoo.second = 0;
    _endRectCoo.second = 0;
    _endRectCoo.first = 0;
    _mouseIsPressed = false;
}

void TileEditorCanvas::OnUpdate()
{
    if(_canvasEnabled != true)
        return;
}

void    TileEditorCanvas::OnDraw()
{
    if(_canvasEnabled != true)
    {
        Clear(sf::Color(187,187,187));
        //        /std::cout << "IS FALSE" << std::endl;
        Display();
    }
    else
    {
        Clear(sf::Color(0,0,0));
        // Draw it
        Draw(_currentTilesetSprite);
        //the last one
        applyLayer(TILE_EDITOR_SCREEN_WIDTH, TILE_EDITOR_SCREEN_HEIGHT,_layerSprite );
        drawCursor();
        Display();
    }
}

void    TileEditorCanvas::setCursorMode(int mode)
{
    if (_cursorMode != RECT_CURSOR_MODE)
    {
        _endRectCoo.first = _beginRectCoo.first;
        _endRectCoo.second = _beginRectCoo.second;
    }
    _cursorMode = mode;
}

void    TileEditorCanvas::setCanvasEnabled(bool state)
{
    _canvasEnabled = state;
    setEnabled(state);
}

void TileEditorCanvas::mouseMoveEvent(QMouseEvent *e)
{
    _endRectCoo.first = ((e->x() / 32) * 32);
    _endRectCoo.second = ((e->y() / 32) * 32);

    (void)e;
}

void TileEditorCanvas::mouseReleaseEvent( QMouseEvent * e )
{
    (void)e;
    if (_canvasEnabled == true)
    {
        if (_cursorMode == RECT_CURSOR_MODE)
        {
            if (MainWindow::_tilesSelected.size())
            {
                MainWindow::_tilesSelectedMapWidth = abs(_beginRectCoo.first - _endRectCoo.first) / 32 + 1;
                MainWindow::_tilesSelectedMapHeight = abs(_beginRectCoo.second - _endRectCoo.second) / 32 + 1;
                MainWindow::_tilesSelected.front().first.first = (_beginRectCoo.first < _endRectCoo.first ? _beginRectCoo.first : _endRectCoo.first);
                MainWindow::_tilesSelected.front().first.second = (_beginRectCoo.second < _endRectCoo.second ? _beginRectCoo.second : _endRectCoo.second);;
            }
        }
    }
}

void TileEditorCanvas::wheelEvent(QWheelEvent* e)
{
    (void)e;
}

void TileEditorCanvas::mousePressEvent ( QMouseEvent * e )
{
    if (_canvasEnabled == true)
    {
        _mouseIsPressed = true;
        MainWindow::_tilesSelected.clear();
        if (_cursorMode == PEN_CURSOR_MODE)
        {
            setSelectedTile(e->x(),e->y());
        }
        else if (_cursorMode == RECT_CURSOR_MODE)
        {
            setSelectedTile(e->x(), e->y());
        }
        else if (_cursorMode == FILL_CURSOR_MODE)
        {
            setSelectedTile(e->x(),e->y());
        }
    }
}

void    TileEditorCanvas::drawCursor()
{
    // Afficher le curseur de selection en fonction du mode specifie (pen / rec / full)

    if (_cursorMode == PEN_CURSOR_MODE)
    {
        drawPenCursor();
    }
    else if (_cursorMode == RECT_CURSOR_MODE)
    {
        drawRectCursor();
    }
    else if (_cursorMode == FILL_CURSOR_MODE)
    {
        drawFillCursor();
    }
}


void TileEditorCanvas::drawPenCursor()
{
    sf::Event Event;
    while (GetEvent(Event))
    {
        if (Event.Type == sf::Event::MouseMoved)
        {
            _frameSprite.SetX((Event.MouseMove.X / 32) * 32 );
            _frameSprite.SetY((Event.MouseMove.Y / 32) * 32 );
        }
    }
    Draw(_frameSprite);
}

void    TileEditorCanvas::drawRectCursor()
{
    sf::Shape Rect;

    if (_endRectCoo.first < 0)
        _endRectCoo.first = 0;
    if (_endRectCoo.first > 224)
        _endRectCoo.first = 224;
    if (_endRectCoo.second < 0)
        _endRectCoo.second = 0;
    if (_endRectCoo.second > 512)
        _endRectCoo.second = 512;
    Rect  =   sf::Shape::Rectangle((_beginRectCoo.first + (_beginRectCoo.first < _endRectCoo.first ? 0 + 4 : 32 - 4)),
                                   (_beginRectCoo.second + (_beginRectCoo.second < _endRectCoo.second ? 0 + 4 : 32 - 4)),
                                   (_endRectCoo.first + (_beginRectCoo.first < _endRectCoo.first ? 32 - 4 : 0 + 4)),
                                   (_endRectCoo.second + (_beginRectCoo.second < _endRectCoo.second ? 32 - 4 : 0 + 4)),
                                   sf::Color(0, 128, 0,0), 4.0f,sf::Color(255, 255, 255) );
    Draw(Rect);
}

void    TileEditorCanvas::drawFillCursor()
{

}

void            TileEditorCanvas::updateTileSet(int index)
{
    sf::Image *img =     ImageManager::singleton().getByRank(index);
    _currentTilesetSprite.SetImage(*img);
    _currentTileSetId = index;
}


void            TileEditorCanvas::setSelectedTile(int x, int y)
{
    _beginRectCoo.first = (x / 32) * 32;
    _beginRectCoo.second = (y / 32) * 32;
    _endRectCoo.first = (x / 32) * 32;
    _endRectCoo.second = (y / 32) * 32;
    MainWindow::_tilesSelectedMapWidth = abs(_beginRectCoo.first - _endRectCoo.first) / 32 + 1;
    MainWindow::_tilesSelectedMapHeight = abs(_beginRectCoo.second - _endRectCoo.second) / 32 + 1;

    std::pair<int,int> selected;

    selected.first = ((x / 32) * 32);
    selected.second = ((y / 32) * 32);


    std::pair<std::pair<int,int>, int> selectedTile;

    selectedTile.first = selected;
    selectedTile.second =  _currentTileSetId;


   MainWindow::_tilesSelected.push_back(selectedTile);
}
