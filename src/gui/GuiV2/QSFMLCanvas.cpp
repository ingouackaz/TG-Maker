////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "QSFMLCanvas.hpp"

// Platform-specific headers
#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#include <iostream>
#endif


////////////////////////////////////////////////////////////
/// Construct the QSFMLCanvas
////////////////////////////////////////////////////////////
QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime) :
    QWidget       (Parent),
    myInitialized (false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer
    myTimer.setInterval(FrameTime);


    // Load the image
    // _selectedImage.LoadFromFile("../resources/selected.png");

    // Setup the sprite
    // _selectedSprite.SetImage(_selectedImage);
}


////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
QSFMLCanvas::~QSFMLCanvas()
{
    // Nothing to do...
}


////////////////////////////////////////////////////////////
/// Notification for the derived class that moment is good
/// for doing initializations
////////////////////////////////////////////////////////////
void QSFMLCanvas::OnInit()
{

}


////////////////////////////////////////////////////////////
/// Notification for the derived class that moment is good
/// for doing its update and drawing stuff
////////////////////////////////////////////////////////////
void QSFMLCanvas::OnUpdate()
{
    // Nothing to do by default...
}

void QSFMLCanvas::OnDraw()
{
    // Nothing to do by default...
}

////////////////////////////////////////////////////////////
/// Called when the widget is shown ;
/// we use it to initialize our SFML window
////////////////////////////////////////////////////////////
void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
#ifdef Q_WS_X11
        XFlush(QX11Info::display());
#endif

        // Create the SFML window with the widget handle
        Create(winId());

        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}


////////////////////////////////////////////////////////////
/// Called when the widget needs to be painted ;
/// we use it to display a new frame
////////////////////////////////////////////////////////////
void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    // Let the derived class do its specific stuff
    OnUpdate();
    OnDraw();
    // Display on screen
    Display();
}

void    QSFMLCanvas::setCanvasEnabled(bool)
{
    // Nothing to do by default...
}

void    QSFMLCanvas::applyLayer(const int width, const int height,sf::Sprite &layer)
{
    (void)width;
    (void)height;
    (void)layer;

    /*
    for (int i = 0; i < (width / 32); ++i)
    {
        for(int x = 0; x < (height / 32); ++x)
        {
            layer.SetPosition( i * 32, x * 32);
            Draw(layer);
        }
    }
    */
}
