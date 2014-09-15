
#ifndef HPP_ARESOURCE
#define HPP_ARESOURCE

template<class T>
class ResourceDeserializer;

class AResource
{
    public:
    virtual ~AResource();

    virtual bool serialize(int fd) const;
    virtual void deserialize(void const* res_data);
    
    virtual void load() = 0;

    virtual unsigned int _res_data_size() const = 0;
    virtual void const* _res_data() const= 0;
    virtual void* _res_data() = 0;
};

template<class T>
class ResourceDeserializer
{
    public:
    static T* make(void* res_data)
    {
        T* new_element(new T());

        new_element->deserialize(res_data);
        return new_element;
    }
};

#endif

