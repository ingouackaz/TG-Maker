
#include "Action.hpp"
#include "Branch.hpp"
#include "ProjectManager.hpp"
#include "Variable.hpp"
#include "Text.hpp"
#include "Position.hpp"
#include "Event.hpp"
#include "Sound.hpp"

Action::Action()
    : m_next(0), m_position(0), m_variable_to(0), m_variable_from(0), m_text(0), m_sound(0)
{
}

void Action::load()
{
    if (res_data.id_next != -1)
    {
        if (res_data.flags & NextIsBranch)
            m_next = &BranchManager::singleton().fetch(res_data.id_next);
        else
            m_next = &ActionManager::singleton().fetch(res_data.id_next);
    }

    switch (res_data.type)
    {
        case VariableAssign:   // var = to_var
            m_variable_to = &VariableManager::singleton().fetch(res_data.variable_assign.id_var_to);
            m_variable_from = &VariableManager::singleton().fetch(res_data.variable_assign.id_var_from);
            break;

        case PlayerMove:
            break;

        case PositionSetImage:
            m_position = &PositionManager::singleton().fetch(res_data.position_image.y * ProjectManagerBase::map_width + res_data.position_image.x);
            break;

        case TextOn:        // TextMgr.activate_text(TextId)
        case TextOff:       // TextMgr.deactivate_text(TextId)
            m_text = &TextManager::singleton().fetch(res_data.id_target);
            break;

        case EventQueue:
            break;

        case SoundOn:       // SoundMgr.activate_sound(SoundId)
        case SoundOff:      // SoundMgr.deactivate_sound(SoundId)
            m_sound = &SoundManager::singleton().fetch(res_data.id_target);
            break;
        
        default:
            throw("Invalid Action type.");
            break;
    }
}

IExecutable* Action::execute()
{
    switch (res_data.type)
    {
        case VariableAssign:         // var = to_var
            m_variable_to->assign(m_variable_from->value());
            break;
            
        case PlayerMove:
            ProjectManager::singleton().player().move(
                VariableManager::singleton().fetch(res_data.player_move.id_x).value(),
                VariableManager::singleton().fetch(res_data.player_move.id_y).value()
            );
            break;

        case PlayerSetImage:
            ProjectManager::singleton().player().apply_image(res_data.player_image.id_image, res_data.player_image.image_tile_at_x, res_data.player_image.image_tile_at_y);
            break;

        case PositionSetImage:
            m_position->apply_image(res_data.position_image.id_image, res_data.position_image.image_tile_at_x, res_data.position_image.image_tile_at_y);
            break;

        case TextOn:
            m_text->res_data.flags |= TextBase::Displayed;
            break;
        
        case TextOff:
            m_text->res_data.flags &= ~TextBase::Displayed;
            break;

        case EventQueue:
            EventManager::singleton().queue(res_data.event_queue.id_event, res_data.event_queue.delay);
            break;

        case SoundOn:
            m_sound->Play();
            break;

        case SoundOff:
            m_sound->Stop();
            break;

        default:
            break;
    }

    return m_next;
}

ActionManager& ActionManager::singleton()
{
    static bool registered(false);
    static ActionManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);
        registered = true;
    }

    return singleton;
}

ActionManager::ActionManager()
    : Manager<Action>(Action::manager_id)
{
}

