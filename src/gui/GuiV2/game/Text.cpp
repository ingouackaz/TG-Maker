
#include "Text.hpp"
#include "ProjectManager.hpp"

void Text::load()
{
    res_data.size = 22;
    res_data.x = 10;
    res_data.y = 600;
    SetSize(res_data.size);
    SetPosition(res_data.x, res_data.y);
}

TextManager& TextManager::singleton()
{
    static bool registered(false);
    static TextManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);
        registered = true;
    }

    return singleton;
}

void TextManager::load()
{
    // load attributes
    Manager<Text>::load();

    // load buffers
    for (TextManager::const_iterator it(this->begin()); it != this->end(); ++it)
    {
        debug(it->first << ": buffer load from " << static_cast<void const*>(m_buffers.buffer(it->first)) << ", size " << it->second->res_data.size << std::endl);
        it->second->SetText(m_buffers.buffer(it->first));
    }
}

TextManager::TextManager()
    : Manager<Text>(Text::manager_id)
{
}

