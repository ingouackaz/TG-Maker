#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class       Session;

class Game
{
public:
    Game();
    void          run();
    sf::RenderWindow *_app;
protected:
    Session    *_session;
    int        _mode;
private:
    Game(const Game &);
    Game &operator=(const Game &);
    void          initialize(void);
    void          update(void);
    void          draw(void);
};

#endif // GAME_HPP
