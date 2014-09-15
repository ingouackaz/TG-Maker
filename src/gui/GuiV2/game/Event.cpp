
#include <SFML/System/Clock.hpp>

#include "Event.hpp"
#include "ProjectManager.hpp"
#include "Branch.hpp"
#include "Action.hpp"

Event::Event()
    : m_first(0)
{
}

void Event::load()
{
    if (res_data.id_first != -1)
    {
        if (res_data.flags & FirstIsBranch)
            m_first = &BranchManager::singleton().fetch(res_data.id_first);
        else
            m_first = &ActionManager::singleton().fetch(res_data.id_first);
    }
}

void Event::execute()
{
    if (res_data.n)
    {
        res_data.n--;
        
        {
            IExecutable* exe(m_first);
            
            while (exe)
                exe = exe->execute();
        }
    }
}

EventManager& EventManager::singleton()
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

bool EventManager::serialize(int fd) const
{
    Header manager_header;

    memcpy(manager_header.base.id, m_manager_id.c_str(), 3);
    manager_header.base.id[3] = 0;
    manager_header.array_sz = (sizeof(int) + sizeof(Event::ResourceData)) * this->size();
    manager_header.queue_sz = (sizeof(float) + sizeof(int)) * m_queue.size();
    manager_header.base.sz =
        (sizeof(Header) - sizeof(IManager::Header)) // include the new header overhead
        + manager_header.array_sz + manager_header.queue_sz;
    
    if (write(fd, &manager_header, sizeof(Header)) == sizeof(Header))
    {
        // Write event res_data
        for (const_iterator it = this->begin(); it != this->end(); ++it)
        {
            if (write(fd, &it->first, sizeof(int)) != sizeof(int) || !it->second->serialize(fd))
                return false;
        }

        // Write queue res_data
        for (std::list< std::pair<float, int> >::const_iterator it(m_queue.begin()); it != m_queue.end(); ++it)
        {
            if (false ||
                write(fd, &it->first, sizeof(float)) != sizeof(float) || 
                write(fd, &it->second, sizeof(int)) != sizeof(int) ||
                false)
                return false;
        }

        return true;
    }

    //TODO GESTION DERREUR PLUS PROPRE
    return false;
}

void EventManager::deserialize(void const* manager_header)
{
    Header const* header(reinterpret_cast<Header const*>(manager_header));

    debug("starting deserialization of manager " << m_manager_id << std::endl);
    for (char* element = (char*)manager_header + sizeof(Header);
        element < (char*)manager_header + header->array_sz;
        element = (char*)element + sizeof(int) + sizeof(ResourceData))
    {
        Event* new_elem(ResourceDeserializer<Event>::make((void*)((char*)element + sizeof(int))));

        (*this)[*(int*)element] = new_elem;
    }

    for (char* element = (char*)manager_header + sizeof(Header) + header->array_sz;
        element < (char*)manager_header + header->queue_sz;
        element = (char*)element + sizeof(float) + sizeof(int))
        queue(*(int*)(element + sizeof(float)), *(float*)element);
}

void EventManager::clear()
{
    Manager<Event>::clear();
    m_queue.clear();
}

bool event_compare(std::pair<float, Event*> const& a, std::pair<float, Event*> const& b)
{
    return a.first < b.first;
}

void EventManager::queue(int id_event, unsigned int delay)
{
    if (id_event != -1)
    {
        std::list< std::pair<float, int> > l;
        
        l.push_front(std::pair<float, int>(delay, id_event));
        m_queue.merge(l, event_compare);
    }
}

void EventManager::pause()
{
    if (!m_clock)
        throw(std::runtime_error("paused twice"));
    debug("game paused" << std::endl);
    delete m_clock;
    m_clock = 0;
}

void EventManager::resume()
{
    if (m_clock)
        throw(std::runtime_error("already unpaused"));
    debug("game resumed" << std::endl);
    m_clock = new sf::Clock;
}

void EventManager::tick()
{
    for (std::list< std::pair<float, int> >::iterator it(m_queue.begin()); it != m_queue.end(); ++it)
        it->first -= m_clock->GetElapsedTime();
    m_clock->Reset();

    while (!m_queue.empty() && m_queue.front().first <= .0f)
    {
        Event* evt(&fetch(m_queue.front().second));

        m_queue.pop_front();
        if (evt->res_data.n > 0)
        {
            // n is decreased at its execution
            //evt->res_data.n--;
            
            evt->execute();
        }
    }
}

EventManager::EventManager()
    : Manager<Event>(Event::manager_id), m_clock(0)
{
}

