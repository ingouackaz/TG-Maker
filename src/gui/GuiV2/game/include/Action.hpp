
#ifndef HPP_ACTION
#define HPP_ACTION

#include "ActionBase.hpp"
#include "IExecutable.hpp"
#include "Manager.hpp"

class Position;
class Variable;
class Text;
class Sound;

class Action : public ActionBase, public IExecutable
{
    public:
    Action();

    virtual void load();

    virtual IExecutable* execute();

    protected:
    IExecutable* m_next;
    Position* m_position;
    Variable* m_variable_to;
    Variable* m_variable_from;
    Text* m_text;
    Sound* m_sound;
};

class ActionManager : public Manager<Action>
{
    public:
    static ActionManager& singleton();

    private:
    ActionManager();
    ActionManager(ActionManager const& m);
};

#endif

