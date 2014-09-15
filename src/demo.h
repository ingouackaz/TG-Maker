/*
Event global WASD de teleport du joueur sur x-1 x+1 y-1 y+1.
Demontrer la collision d'une case par le deplacement.
Setter le sprite du personnage en fonction de sa direction (variable userspace, selon son dernier deplacement).
Touche shift permettant de "sprinter".
Afficher le texte "Sprinting" en 10,500 taille 22 si shift est enfoncee.
Ramasser la cle et conditionner l'acces par une porte par celle-ci.
Jouer un son lors de son passage par la porte.
Lorsqu'il passe sur case ID "eau", setter le sprite "nager". S'il quitte l'eau, reset le sprite.
*/

// VARIABLES
 
int player_x_less;
int player_x_more;
int player_y_less;
int player_y_more;

{
    int less;
    int more;
    int player_x;
    int player_y;
    {   // less, -1
        Variable* v(new Variable);

        v->type = Variable::Constant;
        v->constant = -1;
        less = VariableManager::singleton().push(v);
    }

    {   // more, +1
        Variable* v(new Variable);

        v->type = Variable::Constant;
        v->constant = 1;
        more = VariableManager::singleton().push(v);
    }

    {   // player_x
        Variable* v(new Variable);

        v->type = Variable::PlayerX;
        player_x = Variable::singleton().push(v);
    }

    {   // player_y
        Variable* v(new Variable);

        v->type = Variable::PlayerY;
        player_y = Variable::singleton().push(v);
    }

    {   // player_x - 1
        Variable* v(new Variable);

        v->type = Variable::Addition;
        v->vars.id_a = player_x;
        v->vars.id_b = less;
        player_x_less = VariableManager::singleton().push(v);
    }

    {   // player_x + 1
        Variable* v(new Variable);

        v->type = Variable::Addition;
        v->vars.id_a = player_x;
        v->vars.id_b = more;
        player_x_more = VariableManager::singleton().push(v);
    }

    {   // player_y - 1
        Variable* v(new Variable);

        v->type = Variable::Addition;
        v->vars.id_a = player_y;
        v->vars.id_b = less;
        player_y_less = VariableManager::singleton().push(v);
    }

    {   // player_y + 1
        Variable* v(new Variable);

        v->type = Variable::Addition;
        v->vars.id_a = player_y;
        v->vars.id_b = more;
        player_y_more = VariableManager::singleton().push(v);
    }
}
int id_key_left;
{
    Variable* key_left(new Variable);

    key_left->type = Variable::KeyState;
    key_left->id_key = sf::Keycode::Left;
    id_key_left = VariableManager::singleton().push(key_left);
}
int id_keystate_down;
{
    Variable* keystate_down(new Variable);

    keystate_down->type = Variable::Constant;
    keystate_down->constant = sf::Keydown;
    id_keystate_down = VariableManager::singleton().push(keystate_down);
}
int id_key_shift;
{
    Variable* key_shift(new Variable);

    key_shift->type = Variable::KeyState;
    key_shift->id_key = sf::Keycode::Shift;
    id_key_shift = VariableManager::singleton().push(key_shift);
}

// SCRIPTING

{
    int id_global;
    Event* global(new Event);

    id_global = EventManager::push(global);

    Branch* left_pushed(new Branch);
    {   // if left.keystate==keydown
        left_pushed->res_data.cmptype = Branch::Equal;
        left_pushed->res_Data.vars[0] = id_key_left;
        left_pushed->res_data.vars[1] = id_keystate_down;
        
        {   // then
            {   // move left
                Action* move_left(new Action);

                move_left->res_data.id_next = -1;
                move_left->res_data.type = Action::PlayerMove;
                move_left->res_data.flags = 0;
                move_left->res_data.player_move.id_x = player_x_less;
                move_left->res_data.player_move.id_y = player_y;
                
                left_pushed->res_data.id_then = ActionManager::singleton().push(move_left);
            }

            // Branch end
            move_left->res_data.id_next = -1;
            move_left->res_data.flags = 0;
        }
    }

    Branch* shift_pushed(new Branch);
    {   // if shift.keystate == keydown
        shift_pushed->res_data.cmptype = Branch::Equal;
        shift_pushed->res_data.vars[0] = id_key_shift;
        shift_pushed->res_data.vars[1] = id_keystate_down;

        {   // then
            {   // requeue fast
                Action* requeue_fast(new Action);

                requeue_fast->res_data.type = Action::EventQueue;
                requeue_fast->res_data.event_queue.id_event = id_global;
                requeue_fast->res_data.event_queue.delay = 100;

                shift_pushed->res_data.id_then = ActionManager::singleton().push(requeue_fast);
            }

            // Branch end
            requeue_fast->res_data.id_next = -1;
            requeue_fast->res_data.flags = 0;
        }
    }
    left_pushed->res_data.id_next = BranchManager::singleton().push(shift_pushed);
    left_pushed->res_data.flags = Branch::NextIsBranch;

    Branch* shift_not_pushed(new Branch);
    {   // if shift.keystate == keydown
        shift_not_pushed->res_data.cmptype = Branch::NotEqual;
        shift_not_pushed->res_data.id_next = -1;
        shift_not_pushed->res_data.vars[0] = id_key_shift;
        shift_not_pushed->res_data.vars[1] = id_keystate_down;

        {   // then requeue slow
            Action* requeue_slow(new Action);

            requeue_slow->res_data.type = Action::EventQueue;
            requeue_slow->res_data.flags = 0;
            requeue_slow->res_data.event_queue.id_event = id_global;
            requeue_slow->res_data.event_queue.delay = 500;
            
            shift_pushed->res_data.id_then = ActionManager::singleton().push(requeue_slow);
        }
    }
    shift_pushed->res_data.id_next = BranchManager::singleton().push(shift_not_pushed);
    shift_pushed->res_data.flags = Branch::NextIsBranch;
    
    // Event end, define the edges
    global->res_data.id_first = BranchManager::singleton().push(left_pushed);
    global->res_data.flags = Event::FirstIsBranch;
    shift_not_pushed->res_data.id_next = -1;
    shift_not_pushed->res_data.flags = 0;
    
    /*
    if (Left pushed)
    {
        player_move(addition(x, -1), y);
        //player_setimage(tileset_player, 1, 0);
    }

    if (Shift pushed)
    {
        event_queue(this, 100);
        //text_on(sprint);
    }

    if (!shift_pushed)
    {
        event_queue(this, 500);
        //text_off(sprint);
    }*/
}

