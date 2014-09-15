
#ifndef HPP_PROJECTMANAGERBASE
#define HPP_PROJECTMANAGERBASE

#include <string>

#include "Manager.hpp"

#include <iostream>

template<>
class Manager<IManager> : public IManager, public std::map<std::string, IManager*>
{
    public:
    typedef std::map<std::string, IManager*> Container;
    
    virtual std::string const& id() const
    {
        return dummy;
    }

    // let this method be overidden by the subclass
    virtual void deserialize(void const* manager_header)
    {
        (void)manager_header;
    }

    virtual void load()
    {
        for (const_iterator it(this->begin()); it != this->end(); ++it)
        {
	  debug(it->first << ": loading...\n");
            it->second->load();
        }
    }

    private:
    std::string dummy;
};

class ProjectManagerBase : public Manager<IManager>
{
    public:
    struct PlayerData
    {
        int x;
        int y;
        struct
        {
            int id;
            int at_x;
            int at_y;
        } image;
    };

    struct Meta
    {
        char name[256];
        char author[256];
        PlayerData player;
    };
    
    struct Header
    {
        unsigned int magic;
        Meta meta;
        int sz;             // TOTAL file size
    };

    // magic for the binary file
    static unsigned int const magic;

    // map dimensions
    static int const map_width;
    static int const map_height;
    static unsigned int const tile_width;
    static unsigned int const tile_height;
    static unsigned int const screen_width;
    static unsigned int const screen_height;

    virtual bool serialize(int fd) const;
    virtual void deserialize(void const* main_header);

    bool serialize(std::string const& path) const;
    void deserialize(std::string const& path);
    
    void register_manager(IManager* mgr);
    
    void clear();

    std::string name() const
    {
        return std::string(m_meta.name);
    }

    std::string author() const
    {
        return std::string(m_meta.author);
    }

    void set_name(std::string const& name)
    {
        strncpy(m_meta.name, name.c_str(), sizeof(m_meta.name));
        m_meta.name[sizeof(m_meta.name)-1] = 0;
    }

    void set_author(std::string const& author)
    {
        strncpy(m_meta.author, author.c_str(), sizeof(m_meta.author));
        m_meta.author[sizeof(m_meta.author)-1] = 0;
    }

    Meta const& meta() const
    {
        return m_meta;
    }

    Meta& meta()
    {
        return m_meta;
    }

    protected:
    Meta m_meta;
};

#endif

