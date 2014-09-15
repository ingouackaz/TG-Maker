
#ifndef HPP_IGAMETASK
#define HPP_IGAMETASK

namespace sf
{
    class Event;
};

class Game;

class IGameTask
{
    public:
    virtual ~IGameTask() {}
    virtual float interval() const = 0;
    virtual void handle_event(Game& game, sf::Event const& event) = 0;
    virtual void execute(Game& game) = 0;
    virtual void draw(Game& game) = 0;
};

#endif

