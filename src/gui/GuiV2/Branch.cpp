#include "Branch.hpp"
#include "ProjectManager.hpp"

Branch::Branch()
{

}



BranchManager::BranchManager()
    : Manager<Branch>(Branch::manager_id)
{


}

BranchManager &BranchManager::singleton()
{
    static bool registered(false);
    static BranchManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);

        registered = true;
    }

    return singleton;
}
