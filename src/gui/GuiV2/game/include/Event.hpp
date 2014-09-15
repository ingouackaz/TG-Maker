
#ifndef HPP_EVENT
#define HPP_EVENT

#include <list>

#include "EventBase.hpp"
#include "IExecutable.hpp"
#include "Manager.hpp"

class Branch;

class Event : public EventBase
{
    public:
    Event();

    virtual void load();

    virtual void execute();

    protected:
    IExecutable* m_first;
};

namespace sf
{
    class Clock;
};

class EventManager : public Manager<Event>
{
    public:
    static EventManager& singleton();
    
    // overload of Manager<Event> to serialize/deserialize the queue
    virtual bool serialize(int fd) const;
    virtual void deserialize(void const* manager_header);
    virtual void clear();

    // queue an event to be triggered after "delay" ticks
    void queue(int id_event, unsigned int delay);

    void pause();
    void resume();

    // call this at every frame to trigger queued events
    void tick();

    private:
    EventManager();
    EventManager(EventManager const& m);

    static bool event_compare(std::pair<float, int> const& a, std::pair<float, int> const& b)
    {
        return a.first < b.first;
    }

    struct Header
    {
        IManager::Header base;
        int array_sz;   // in bytes
        int queue_sz;   // in bytes 
    };

    std::list< std::pair<float, int> > m_queue;
    sf::Clock* m_clock;
};

#endif

