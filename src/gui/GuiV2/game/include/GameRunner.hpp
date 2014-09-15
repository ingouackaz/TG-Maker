
#ifndef HPP_GAMERUNNER
#define HPP_GAMERUNNER

#include "IGameTask.hpp"

class EventQueue;

class GameRunner : public IGameTask
{
    public:
    static float const interval_time;

    GameRunner();
    
    // IGameTask implementation
    virtual float interval() const;
    virtual void handle_event(Game& game, sf::Event const& event);
    virtual void execute(Game& game);
    virtual void draw(Game& game);

    void pause();
    void resume();
};

#endif

