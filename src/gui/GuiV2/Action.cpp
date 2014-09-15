
#include <sstream>

#include "Action.hpp"
#include "Variable.hpp"
#include "ProjectManager.hpp"

Action::Action()
{

}

void Action::set_Action(ActionType type, int id_target)
{
    res_data.type = type;
    res_data.id_target = id_target;
}

void Action::set_Action(ActionType type, int a, int b)
{
    res_data.type = type;
    // FUCK IT ON SET TOUTES LES STRUCTS DE 2 VARIABLES DE LA MEME FACON
    res_data.variable_assign.id_var_to = a;
    res_data.variable_assign.id_var_from = b;
}

void Action::set_Action(ActionType type, int id_image, int tile_at_x, int tile_at_y)
{
    res_data.type = type;
    res_data.player_image.id_image = id_image;
    res_data.player_image.image_tile_at_x = tile_at_x;
    res_data.player_image.image_tile_at_y = tile_at_y;
}

void Action::set_Action(ActionType type, int x, int y, int id_image, int tile_at_x, int tile_at_y)
{
    res_data.type = type;
    res_data.position_image.x = x;
    res_data.position_image.y = y;
    res_data.position_image.id_image = id_image;
    res_data.position_image.image_tile_at_x = tile_at_x;
    res_data.position_image.image_tile_at_y = tile_at_y;
}

/*
Event -> first branch
branch -> next action ou branch, first action if, first action else
action -> branch ou action
-1 si fin
*/

std::string Action::to_str() const
{
    std::stringstream ss;

    switch (res_data.type)
    {
        case VariableAssign:   // var = to_var
            {
                Variable* a(VariableManager::singleton().fetch_safe(res_data.variable_assign.id_var_from));
                Variable* b(VariableManager::singleton().fetch_safe(res_data.variable_assign.id_var_to));

                ss << (a ? a->res_data.name : "?") << " = " << (b ? b->res_data.name : "?");
            }
            break;

        case PlayerMove:
                ss << "move player at (var(" << res_data.player_move.id_x << "), (" << res_data.player_move.id_y << "))";
            break;

        case PositionSetImage:
                ss << "position(" << res_data.position_image.x << "," << res_data.position_image.y << ").image to " << res_data.position_image.id_image;
            break;
/*
        case TextOn:        // TextMgr.activate_text(TextId)
            break;
        case TextOff:       // TextMgr.deactivate_text(TextId)
            m_text = &TextManager::singleton().fetch(res_data.id_target);
            break;

        case EventQueue:
            break;

        case SoundOn:       // SoundMgr.activate_sound(SoundId)
            break;
        case SoundOff:      // SoundMgr.deactivate_sound(SoundId)
            break;
*/
        default:
            ss << "some action\n";
            break;
    }
    return ss.str();
}

ActionManager::ActionManager()
    : Manager<Action>(Action::manager_id)
{


}

ActionManager &ActionManager::singleton()
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
