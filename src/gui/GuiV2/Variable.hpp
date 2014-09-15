#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Manager.hpp"
#include "VariableBase.hpp"

class Variable : public VariableBase
{
public:
    Variable();
    void set_Variable(VariableType type);
    void set_Variable(VariableType type, int a);
    void set_Variable(VariableType type, int a, int b);

    void set_name(std::string const& name);

public:
    void load()
    {

    }
};

class VariableManager : public Manager<Variable>
{
private:
    VariableManager();

public:
    static VariableManager &singleton();
};

#endif // VARIABLE_HPP
