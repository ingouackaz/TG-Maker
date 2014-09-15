
#ifndef HPP_BRANCHBASE
#define HPP_BRANCHBASE

#include "AResource.hpp"
#include "Manager.hpp"

class BranchBase : public AResource
{
    public:
    static char const* const manager_id;

    enum BranchCompare
    {
        Equal,
        NotEqual,
        Lesser,
        Greater,
        LesserOrEqual,
        GreaterOrEqual,
        BranchCompareTotal,
    };

    enum BranchFlag
    {
        IsWhile=(1<<0),
        NextIsBranch=(1<<1),
        IfIsBranch=(1<<2),
        //ElseIsBranch=(1<<3),
    };

    typedef struct 
    {
        int id_next;            // id of the condition branch or action following the branch
        int flags;              // see BranchFlag
        BranchCompare cmptype;  // how to compare the two variables
        int id_vars[2];         // variables to compare
        int id_then;            // first action OR branch in the IF scope
//        int id_else;            // first action OR branch in the ELSE scope (ignored if flags & IsWhile)
        /*
            // in a nutshell
            loop:
            if (VariableManager::get_var(id_vars[0]) cmptype VariableManager::get_var(id_vars[1]))
            {
                if (id_action_then >= 0)
                    ActionManager::execute(id_action_then);
                if (flags & IsWhile)
                    goto loop;
            }
            else
            {
                if (!(flags & IsWhile) && id_action_else >= 0)
                    ActionManager::execute(id_action_else);
            }
        */
    } ResourceData;
    
    ResourceData res_data;

    protected:
    virtual unsigned int _res_data_size() const;
    virtual void const* _res_data() const;
    virtual void* _res_data();
};

#endif

