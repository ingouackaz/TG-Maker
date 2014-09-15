
#ifndef HPP_PROJECTMANAGER
#define HPP_PROJECTMANAGER

#include "ProjectManagerBase.hpp"
#include "Debug.hpp"

#include "Player.hpp"

class ProjectManager : public ProjectManagerBase
{
    public:
    static ProjectManager& singleton();
    
    virtual void load();
    
    void load_new_game();

    Player const& player() const
    {
        return *m_player;
    }

    Player& player() 
    {
        return *m_player;
    }

    private:
    ProjectManager();
    ProjectManager(ProjectManager const& m);
    void _init_resources();

    Player* m_player;
};

#endif

