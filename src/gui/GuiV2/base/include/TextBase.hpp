
#ifndef HPP_TEXTBASE
#define HPP_TEXTBASE

#include "AResource.hpp"
#include "Manager.hpp"

class Text;

class TextBase : public AResource
{
    public:
    static char const* const manager_id;
    
    enum TextFlag
    {
        Displayed=(1<<0),
    };

    typedef struct
    {
        char path[256];
        int flags;
        int x;
        int y;
        int size;
    } ResourceData;
    
    ResourceData res_data;

    protected:
    virtual unsigned int _res_data_size() const;
    virtual void const* _res_data() const;
    virtual void* _res_data();
};

#endif

