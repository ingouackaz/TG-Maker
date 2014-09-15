
#ifndef HPP_IMANAGER
#define HPP_IMANAGER

#include <string>

class IManager
{
    public:
    struct Header
    {
        char id[4]; // manager id (three characters + NULL)
        int sz;     // manager size
    };

    struct ResourceData {};
    virtual ~IManager() {}
    virtual std::string const& id() const = 0;
    virtual bool serialize(int fd) const = 0;
    virtual void deserialize(void const* p) = 0;
    virtual void load() = 0;
    virtual void clear() = 0;
};

#endif

