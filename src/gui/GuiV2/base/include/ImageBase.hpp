
#ifndef HPP_IMAGEBASE
#define HPP_IMAGEBASE

#include "AResource.hpp"

class ImageBase : public AResource
{
    public:
    static char const* const manager_id;
    
    typedef struct
    {
        char path[256];
        unsigned int size;
    } ResourceData;
  
    ResourceData res_data;
    
    protected:
    virtual unsigned int _res_data_size() const;
    virtual void const* _res_data() const;
    virtual void* _res_data();
};

#endif

