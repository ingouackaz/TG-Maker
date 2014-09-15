
#ifndef HPP_MANAGER
#define HPP_MANAGER

#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <map>

#include "IManager.hpp"
#include "Debug.hpp"

#include "AResource.hpp"

template<class T>
class Manager : public IManager, public std::map<int, T*>
{
    protected:
    typedef std::map<int, T*> Container;
    public:
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::iterator iterator;

    Manager(std::string const& id)
        : m_manager_id(id)
    {
        assert(m_manager_id.size() == 3);
    }

    ~Manager()
    {
        clear();
    }

    virtual std::string const& id() const
    {
        return m_manager_id;
    }

    virtual int push(T* element)
    {
        int i;

        for (i = 0; this->find(i) != this->end(); ++i);
        (*this)[i] = element;
        return i;
    }

    int id_of(T const* element) const
    {
        for (const_iterator it(this->begin()); it != this->end(); ++it)
        {
            if (it->second == element)
                return it->first;
        }

        return -1;
    }

    T const* fetch_safe(int id) const
    {
        const_iterator it(this->find(id));

        if (it == this->end())
            return 0;

        return it->second;
    }

    T* fetch_safe(int id)
    {
        return const_cast<T*>(fetch_safe(id));
    }

    T const& fetch_const(int id) const
    {
        T const* element(fetch_safe(id));

        if (!element)
        {
            std::stringstream ss;

            ss << T::manager_id << ": element " << id << " not found." << std::endl;
            throw(std::runtime_error(ss.str()));
        }

        return *element;
    }

    T& fetch(int id)
    {
        T const& ret(fetch_const(id));

        return const_cast<T&>(ret);
    }

    virtual T* getByRank(int rank)
    {
        int i = 0;

        for (iterator it = this->begin(); it != this->end(); ++it)
        {
            if (i == rank)
                return (*it).second;
            ++i;
        }
        return 0;
    }

    virtual int getIdByRank(int rank)
    {
        int i = 0;

        for (iterator it = this->begin(); it != this->end(); ++it)
        {
            if (i == rank)
            return (*it).first;
            ++i;
        }
        return 0;
    }

    virtual bool serialize(int fd) const
    {
        IManager::Header manager_header;

        memcpy(manager_header.id, m_manager_id.c_str(), 3);
        manager_header.id[3] = 0;
        manager_header.sz = (sizeof(int) + sizeof(typename T::ResourceData)) * this->size();
        if (write(fd, &manager_header, sizeof(IManager::Header)) == sizeof(IManager::Header))
        {
            for (const_iterator it = this->begin(); it != this->end(); ++it)
            {
                if (write(fd, &it->first, sizeof(int)) != sizeof(int) || !it->second->serialize(fd))
                    return false;
            }
            return true;
        }

        //TODO GESTION DERREUR PLUS PROPRE
        return false;
    }

    virtual void deserialize(void const* manager_header)
    {
        for (char* element = (char*)manager_header + sizeof(IManager::Header);
            element < (char*)manager_header + ((IManager::Header*)manager_header)->sz;
            element = (char*)element + sizeof(int) + sizeof(typename T::ResourceData))
        {
            T* new_elem(ResourceDeserializer<T>::make((void*)((char*)element + sizeof(int))));

            (*this)[*(int*)element] = new_elem;
        }
    }

    virtual void clear()
    {
        for (iterator it(this->begin()); it != this->end(); ++it)
            delete it->second;
        std::map<int, T*>::clear();
    }

    virtual void load()
    {
        for (const_iterator it(this->begin()); it != this->end(); ++it)
            it->second->load();
        debug(m_manager_id << ": loaded " << this->size() << " elements "<< std::endl);
    }

    protected:
    std::string m_manager_id;
    int m_next_id;
};

#endif

