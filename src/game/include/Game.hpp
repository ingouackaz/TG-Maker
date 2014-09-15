
#ifndef HPP_GAME
#define HPP_GAME

#include <SFML/Graphics.hpp>

#include "ProjectManager.hpp"

class IGameTask;

class Game : public sf::RenderWindow
{
    public:
    Game();
    void switch_task(IGameTask* task);
    int run();

    protected:
    IGameTask* m_task;
};

#endif

