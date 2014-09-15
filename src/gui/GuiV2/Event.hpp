#ifndef EVENT_HPP
#define EVENT_HPP

#include <QTreeWidget>

#include "Manager.hpp"
#include "EventBase.hpp"

class Event : public EventBase , public QTreeWidgetItem
{
public:
    Event();

public:
    void load()
    {

    }
};

class EventManager : public Manager<Event>
{
private:
    EventManager();

public:
    static EventManager &singleton();
};

#endif // EVENT_HPP
