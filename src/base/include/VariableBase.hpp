
#ifndef HPP_VARIABLEBASE
#define HPP_VARIABLEBASE

#include "AResource.hpp"
#include "Manager.hpp"

class VariableBase : public AResource
{
    public:
    static char const* const manager_id;
    
    enum VariableType
    {
        Constant,               // constant
        Addition,               // constant
        PlayerX,                // none
        PlayerY,                // none
        PositionCollidable,     // pos
        PositionState,          // pos
        EventCounter,           // id_event
        KeyState,               // id_key
        VariableTypeTotal,
    };

    typedef struct
    {
        VariableType type;
        union
        {
            int constant;   // Constant
            struct
            {
                int id_a;
                int id_b;
            } vars;
            struct  // PositionCollidable, PositionState
            {
                int x;     // map.position_is_collidable(x, y) or
                int y;     // map.position_state(x, y)
            } pos;
            int id_event;   // EventDelay, EventCounter: EventMgr.get(EventId).[delay|counter]()
            int id_key;     // sf::Keyboard::???
        };
        char name[256];
    } ResourceData;
    
    ResourceData res_data;

    protected:
    virtual unsigned int _res_data_size() const;
    virtual void const* _res_data() const;
    virtual void* _res_data();
};

#endif

