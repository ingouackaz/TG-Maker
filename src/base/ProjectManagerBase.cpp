
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>

#include "Debug.hpp"
#include "ProjectManagerBase.hpp"

unsigned int const ProjectManagerBase::magic        = 0x42421134;

int const ProjectManagerBase::map_width    = 100;
int const ProjectManagerBase::map_height   = 100;
unsigned int const ProjectManagerBase::tile_width   = 32;
unsigned int const ProjectManagerBase::tile_height  = 32;
unsigned int const ProjectManagerBase::screen_width = 800;
unsigned int const ProjectManagerBase::screen_height= 600;

void ProjectManagerBase::register_manager(IManager* mgr)
{
    assert((*this).find(mgr->id()) == (*this).end());

    //debug(std::string(mgr->id()) + " registered" << std::endl);
    (*this)[mgr->id()] = mgr;
}

bool ProjectManagerBase::serialize(int fd) const
{
    Header main_header;

    main_header.magic = ProjectManagerBase::magic;
    main_header.meta = m_meta;
    write(fd, &main_header, sizeof(Header));
    
    for (Container::const_iterator it = this->begin(); it != this->end(); ++it)
    {
        if (!(*it).second->serialize(fd))
        {
            debug("serialize of " << it->first << ": failed" << std::endl);
            return false;
        }
        debug("serialize of " << it->first << ": success" << std::endl);

        //TODO GERER LE RETOUR DES SERIALIZE DES MANAGERS
    }

    main_header.sz = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    write(fd, &main_header, sizeof(Header));
    return true;
}

void ProjectManagerBase::deserialize(void const* main_header)
{

    memcpy(&m_meta, &((Header*)main_header)->meta, sizeof(Meta));

    debug("main header's size is " << sizeof(Header) << std::endl);
    debug("manager header's size is " << sizeof(IManager::Header) << std::endl);

    for (IManager::Header* manager_header = (IManager::Header*)((char*)main_header + sizeof(Header));
        (char*)manager_header < (char*)main_header + ((Header*)main_header)->sz;
        manager_header = (IManager::Header*)((char*)manager_header + sizeof(IManager::Header) + manager_header->sz))
    {
        debug("starting deserialization of manager " << manager_header->id << " of size " << manager_header->sz << std::endl);
        if (manager_header->sz < 0)
        {
            std::stringstream ss;

            ss << "manager header " << manager_header->id << "'s size is negative (" << manager_header->sz << ")." << std::endl;
            throw(std::runtime_error(ss.str()));
        }

        if (this->find(manager_header->id) != this->end())
            (*this)[manager_header->id]->deserialize(manager_header);
        else
        {
            std::stringstream ss;

            ss << "Manager with identifier " << manager_header->id << " not found, offset " << (void*)((char*)manager_header - (char*)main_header) << ".";
            throw std::runtime_error(ss.str());
        }
        debug("deserialization of manager " << manager_header->id << " done" << std::endl);
    }

    //TODO GERER LES ERREURS, + PROPRE (clear tous s'il y en a un qui pete ? // voir si le manager existe dans (*this))
}

bool ProjectManagerBase::serialize(std::string const& path) const
{
    bool ret(false);
    int fd;

    if ((fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
    {
        ret = serialize(fd);
        close(fd);
    }

    return ret;
}

void ProjectManagerBase::deserialize(std::string const& path)
{
    int fd;

    this->clear();
    if ((fd = open(path.c_str(), O_RDONLY)) >= 0)
    {
        void* file;

        if ((file = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0)) != MAP_FAILED)
        {
            Header* main_header((Header*)file);

            if (main_header->magic == ProjectManagerBase::magic && main_header->sz == lseek(fd, 0, SEEK_END))
                deserialize(file);
            else
                throw std::runtime_error("Bad binary file header");
        }
        else
            throw std::runtime_error("Failed to mmap.");

        close(fd);
    }
    else
        throw std::runtime_error("Open failed.");
    
    load();
}

void ProjectManagerBase::clear()
{
    debug("clearing ProjectManagerBase" << std::endl);
    for (Container::const_iterator it = this->begin(); it != this->end(); ++it)
        it->second->clear();
    debug("cleared ProjectManagerBase" << std::endl);
}

