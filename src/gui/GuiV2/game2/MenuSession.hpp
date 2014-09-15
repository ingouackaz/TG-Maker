#ifndef MENUSESSION_HPP
#define MENUSESSION_HPP

#include "Session.hpp"
#include "Game.hpp"

class MenuSession : public Session
{
public:
    MenuSession();
    virtual ~MenuSession();
    virtual Session *update(Game &);
    virtual void draw(Game &);
private:
    sf::Image _menuImage;
    sf::Sprite _menuSprite;
    sf::Image _cursorImage;
    sf::Sprite _cursorSprite;
    sf::Font   _myFont;

    int         _mode;
};

#endif // MENUSESSION_HPP
