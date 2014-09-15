
#ifndef HPP_POSITIONBASE
#define HPP_POSITIONBASE

#include "AResource.hpp"
#include "Manager.hpp"

class PositionBase : public AResource
{
    public:
    static char const* const manager_id;
    
    enum EventFlag
    {
        IsCollidable=(1<<0),
    };
    
    typedef struct
    {
        int x;
        int y;
        int flags;
        int state;
        int id_event;
        int event_delay;
        int id_image;
        int image_tile_at[2];
    } ResourceData;

    ResourceData res_data;

    protected:
    virtual unsigned int _res_data_size() const;
    virtual void const* _res_data() const;
    virtual void* _res_data();
};

#endif

