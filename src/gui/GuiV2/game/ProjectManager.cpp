
#include "ProjectManager.hpp"
#include "Player.hpp"

void ProjectManager::load()
{
    delete m_player;
    m_player = new Player;
    ProjectManagerBase::load();
}

ProjectManager& ProjectManager::singleton()
{
    static ProjectManager singleton;

    return singleton;
}

ProjectManager::ProjectManager()
    : m_player(0)
{
}

