#include "MenuSession.hpp"
#include "GameSession.hpp"
#include <iostream>

MenuSession::MenuSession()
{
    if (!_menuImage.LoadFromFile("menu_image.png"))
        std::cout << "Image is missing" << std::endl;

    _menuSprite.SetImage(_menuImage);
    //  if (!_myFont.LoadFromFile(("millenia.ttf"), 50))
    //   std::cout << "Font is missing" << std::endl;

    if (!_cursorImage.LoadFromFile("cursor_hand.png"))
        std::cout << "Image is missing" << std::endl;

    _cursorSprite.SetImage(_cursorImage);
    _cursorSprite.SetPosition(300.f, 240.f);

    _mode = 0;


}

MenuSession::~MenuSession()
{

}

Session*   MenuSession::update(Game &game)
{
    sf::Event Event;
    while (game._app->GetEvent(Event))
    {
        // Close window : exit
        if (Event.Type == sf::Event::Closed)
            return NULL;

        // Escape key : exit
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            return NULL;
        if(game._app->GetInput().IsKeyDown(sf::Key::Up))
        {
            _mode--;
            if (_mode < 0)
                _mode = 3;
             _cursorSprite.SetPosition(300.f,240.f + (_mode * 36));
        }
        if(game._app->GetInput().IsKeyDown(sf::Key::Down))
        {
            _mode++;
            if (_mode > 3)
            {
                _mode = 0;
            }
             _cursorSprite.SetPosition(300.f,240.f + (_mode * 36));
        }
        if(game._app->GetInput().IsKeyDown(sf::Key::Return))
        {
            if (_mode == 0)
            {
                std::cout << "GAME LAUCHED" << std::endl;
                return new GameSession();
                // return Session Game
            }
            else if (_mode == 3)
            {
                return NULL;
            }
        }
    }
    return this;
}

void    MenuSession::draw(Game &game)
{
    game._app->Draw(_menuSprite);
    game._app->Draw(_cursorSprite);
}


