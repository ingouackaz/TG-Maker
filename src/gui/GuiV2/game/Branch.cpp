
#include "Branch.hpp"
#include "ProjectManager.hpp"
#include "Variable.hpp"
#include "Action.hpp"

static bool compare_equal(int a, int b)
{
    return a == b;
}

static bool compare_not_equal(int a, int b)
{
    return a != b;
}

static bool compare_lesser(int a, int b)
{
    return a < b;
}

static bool compare_greater(int a, int b)
{
    return a > b;
}

static bool compare_lesserorequal(int a, int b)
{
    return a <= b;
}

static bool compare_greaterorequal(int a, int b)
{
    return a >= b;
}

bool (*Branch::compare[BranchCompareTotal])(int, int) =
{
    compare_equal,
    compare_not_equal,
    compare_lesser,
    compare_greater,
    compare_lesserorequal,
    compare_greaterorequal,
};

Branch::Branch()
    : m_next(0), m_var_a(0), m_var_b(0), m_then(0)//, m_else(0)
{
}

void Branch::load()
{
    if (res_data.id_next != -1)
    {
        if (res_data.flags & NextIsBranch)
            m_next = &BranchManager::singleton().fetch(res_data.id_next);
        else
            m_next = &ActionManager::singleton().fetch(res_data.id_next);
    }

    if (res_data.id_then != -1)
    {
        if (res_data.flags & IfIsBranch)
            m_then = &BranchManager::singleton().fetch(res_data.id_then);
        else
            m_then = &ActionManager::singleton().fetch(res_data.id_then);
    }
/*
    if (res_data.id_else != -1)
    {
        if (res_data.flags & ElseIsBranch)
            m_else = &BranchManager::singleton().fetch(res_data.id_else);
        else
            m_else = &ActionManager::singleton().fetch(res_data.id_else);
    }
*/
}

IExecutable* Branch::execute()
{
    bool (*compare)(int, int) = Branch::compare[res_data.cmptype];
    IExecutable* ret(0);
   
    while_label:
    if (compare(m_var_a->value(), m_var_b->value()))
    {
        ret = m_then->execute();
        if (res_data.flags & IsWhile)
            goto while_label;
    }
    //else
    //    ret = m_else->execute();

    return ret;
}

BranchManager& BranchManager::singleton()
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

BranchManager::BranchManager()
    : Manager<Branch>(Branch::manager_id)
{
}

