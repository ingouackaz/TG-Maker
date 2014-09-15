
#ifndef HPP_BRANCH
#define HPP_BRANCH

#include "BranchBase.hpp"
#include "IExecutable.hpp"
#include "Manager.hpp"

class Variable;
class Action;

class Branch : public BranchBase, public IExecutable
{
    public:
    static bool (*compare[BranchBase::BranchCompareTotal])(int, int);

    Branch();

    virtual void load();

    virtual IExecutable* execute();

    protected:
    IExecutable* m_next;
    Variable* m_var_a;
    Variable* m_var_b;
    IExecutable* m_then;
    //IExecutable* m_else;
};

class BranchManager : public Manager<Branch>
{
    public:
    static BranchManager& singleton();

    private:
    BranchManager();
    BranchManager(BranchManager const& m);
};

#endif

