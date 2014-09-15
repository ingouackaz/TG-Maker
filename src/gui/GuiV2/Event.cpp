#include "Event.hpp"
#include "ProjectManager.hpp"

Event::Event()
{

}



EventManager::EventManager()
    : Manager<Event>(Event::manager_id)
{


}

EventManager &EventManager::singleton()
{
    static bool registered(false);
    static EventManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);

        registered = true;
    }

    return singleton;
}
