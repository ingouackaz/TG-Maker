
#include <SFML/Window/Input.hpp>

#include "Variable.hpp"
#include "ProjectManager.hpp"
#include "Position.hpp"
#include "Event.hpp"

Variable::Variable()
    : m_player(0), m_position(0), m_event(0)
{
}

void Variable::load()
{
    switch (res_data.type)
    {
        case Constant:
            break;

        case Addition:
            m_var_a = &VariableManager::singleton().fetch(res_data.vars.id_a);
            m_var_b = &VariableManager::singleton().fetch(res_data.vars.id_b);
            break;

        case PlayerX:
        case PlayerY:
            m_player = &ProjectManager::singleton().player();
            break;

        case PositionCollidable:
        case PositionState:
            {
                PositionManager::iterator it(PositionManager::singleton().find(res_data.pos.y * ProjectManagerBase::map_width + res_data.pos.x));
                m_position = it->second;
            }
            break;

        case EventCounter:
            if (res_data.id_event != -1)
            {
                EventManager::iterator it(EventManager::singleton().find(res_data.id_event));
                m_event = it->second;
            }
            break;

        case KeyState:
            break;

        default:
            throw(std::runtime_error("Invalid Variable type."));
            break;
    }
}

int Variable::value() const
{
    switch (res_data.type)
    {
        case Constant:
            return res_data.constant;

        case Addition:
            return m_var_a->value() + m_var_b->value();

        case PlayerX:
            return m_player->x();

        case PlayerY:
            return m_player->y();
        
        case PositionCollidable:
            return m_position->res_data.flags & PositionBase::IsCollidable;
        
        case PositionState:
            return m_position->res_data.state;
        
        case EventCounter:
            return m_event->res_data.n;
        
        case KeyState:
            return VariableManager::singleton().input().IsKeyDown(static_cast<sf::Key::Code>(res_data.id_key));
        
        default:
            return -1;
    }
}

void Variable::assign(int value)
{
    switch (res_data.type)
    {
        case Constant:
            res_data.constant = value;
            break;

        case PlayerX:
            m_player->move(value, m_player->y());
            break;

        case PlayerY:
            m_player->move(m_player->x(), value);
            break;
        
        case PositionCollidable:
            if (value)
                m_position->res_data.flags |= PositionBase::IsCollidable;
            else
                m_position->res_data.flags &= ~PositionBase::IsCollidable;
            break;

        case PositionState:
            m_position->res_data.state = value;
            break;
        
        case EventCounter:
            m_event->res_data.n = value;
            break;
        
        default:
            break;
    }
}

VariableManager& VariableManager::singleton()
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

VariableManager::VariableManager()
    : Manager<Variable>(Variable::manager_id)
{
}

