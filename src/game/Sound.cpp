
#include "Sound.hpp"
#include "ProjectManager.hpp"

SoundManager& SoundManager::singleton()
{
    static bool registered(false);
    static SoundManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);
        registered = true;
    }

    return singleton;
}

void SoundManager::load()
{
    // load attributes
    Manager<Sound>::load();

    // load buffers
    for (SoundManager::const_iterator it(this->begin()); it != this->end(); ++it)
    {
        debug(it->first << ": buffer load from " << static_cast<void const*>(m_buffers.buffer(it->first)) << ", size " << it->second->res_data.size << std::endl);
        if (!it->second->LoadFromMemory(m_buffers.buffer(it->first), it->second->res_data.size))
            throw std::runtime_error(std::string("Bad Sound file buffer for ") + it->second->res_data.path);
        it->second->SetBuffer(*it->second);
    }
}

SoundManager::SoundManager()
    : Manager<Sound>(Sound::manager_id)
{
}

