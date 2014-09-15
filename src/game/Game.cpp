
#include <SFML/System/Clock.hpp>

#include "Game.hpp"
#include "ProjectManager.hpp"
#include "GameMenu.hpp"
#include "Variable.hpp"

Game::Game()
    : sf::RenderWindow(sf::VideoMode(800, 600, 32), ProjectManager::singleton().name()), m_task(new GameMenu)
{
    VariableManager::singleton().set_input(&GetInput());
    ProjectManager::singleton().load_new_game();
}

void Game::switch_task(IGameTask* task)
{
    delete m_task;
    m_task = task;
}

int Game::run()
{
    bool execute(true);
    sf::Clock clock;

    while (m_task)
    {
        for (sf::Event event; m_task && GetEvent(event);
            m_task->handle_event(*this, event));

        if (m_task)
        {
            if (execute)
            {
                m_task->execute(*this);
                clock.Reset();
                execute = false;
            }

            if (clock.GetElapsedTime() >= m_task->interval())
                execute = true;
            
            SetView(GetDefaultView());
            Clear();
            m_task->draw(*this);
            Display();
        }

    }

    return 0;
}

