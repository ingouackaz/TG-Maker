
#ifndef HPP_VARIABLE
#define HPP_VARIABLE

#include "VariableBase.hpp"

class Player;
class Position;
class Event;

class Variable : public VariableBase
{
    public:
    Variable();

    virtual void load();

    int value() const;
    void assign(int value);

    protected:
    Variable* m_var_a;
    Variable* m_var_b;
    Player* m_player;
    Position* m_position;
    Event* m_event;
};

#include "Manager.hpp"

namespace sf
{
    class Input;
};

class VariableManager : public Manager<Variable>
{
    public:
    static VariableManager& singleton();
    
    sf::Input const& input() const
    {
        return *m_input;
    }

    void set_input(sf::Input const* input)
    {
        m_input = input;
    }

    private:
    VariableManager();
    VariableManager(VariableManager const& m);

    sf::Input const* m_input;
};

#endif

