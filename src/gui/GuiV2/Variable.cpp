#include <cstring>

#include "Variable.hpp"
#include "ProjectManager.hpp"

Variable::Variable()
{

}

void Variable::set_Variable(VariableType type)
{
    res_data.type = type;
    set_name("unnamed variable");
}

void Variable::set_Variable(VariableType type, int a)
{
    res_data.type = type;
    switch (type)
    {
        case Constant:
            res_data.constant = a;
            break;
        case EventCounter:
            res_data.id_event = a;
            break;
        case KeyState:
            res_data.id_key = a;
            break;
        default:
            break;
    }
    set_name("unnamed variable");
}

void Variable::set_Variable(VariableType type, int a, int b)
{
    res_data.type = type;
    switch (type)
    {
        case Addition:
            res_data.vars.id_a = a;
            res_data.vars.id_b = b;
            break;
        case PositionCollidable:
        case PositionState:
            res_data.pos.x = a;
            res_data.pos.y = a;
            break;
        default:
            break;
    }
    set_name("unnamed variable");
}

void Variable::set_name(std::string const& name)
{
    strncpy(res_data.name, name.c_str(), sizeof(res_data.name));
    res_data.name[sizeof(res_data.name)-1] = 0;
}

VariableManager::VariableManager()
    : Manager<Variable>(Variable::manager_id)
{


}

VariableManager &VariableManager::singleton()
{
    static bool registered(false);
    static VariableManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);

        registered = true;
    }

    return singleton;
}
