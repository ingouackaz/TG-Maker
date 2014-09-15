
#include "Image.hpp"
#include "ProjectManager.hpp"

ImageManager& ImageManager::singleton()
{
    static bool registered(false);
    static ImageManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);
        registered = true;
    }

    return singleton;
}

void ImageManager::load()
{
    // load attributes
    Manager<Image>::load();

    // load buffers
    for (ImageManager::const_iterator it(this->begin()); it != this->end(); ++it)
    {
        debug(it->first << ": buffer load from " << static_cast<void const*>(m_buffers.buffer(it->first)) << ", size " << it->second->res_data.size << std::endl);
        if (!it->second->LoadFromMemory(m_buffers.buffer(it->first), it->second->res_data.size))
            throw std::runtime_error(std::string("Bad Image file buffer for ") + it->second->res_data.path);
    }
}


ImageManager::ImageManager()
    : Manager<Image>(Image::manager_id)
{
}

