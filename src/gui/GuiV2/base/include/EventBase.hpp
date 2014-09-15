
#ifndef HPP_EVENTBASE
#define HPP_EVENTBASE

#include <list>

#include "AResource.hpp"
#include "Manager.hpp"

class Event;

class EventBase : public AResource
{
    public:
    static char const* const manager_id;
    
    enum EventFlag
    {
        FirstIsBranch=(1<<0),
    };

    typedef struct 
    {
        int id_first;   // id of the event's first condition branch or action
        int flags;      //
        int n;          // number of remaining calls available
        char name[256]; // description
    } ResourceData;
    
    ResourceData res_data;

    protected:
    virtual unsigned int _res_data_size() const;
    virtual void const* _res_data() const;
    virtual void* _res_data();
};

#endif

