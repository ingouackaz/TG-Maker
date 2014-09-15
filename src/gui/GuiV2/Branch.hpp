#ifndef BRANCH_HPP
#define BRANCH_HPP

#include <QTreeWidget>

#include "Manager.hpp"
#include "BranchBase.hpp"

class Branch : public BranchBase , public QTreeWidgetItem
{
public:
    Branch();
public:
    void load()
    {

    }
};

class BranchManager : public Manager<Branch>
{
private:
    BranchManager();

public:
    static BranchManager &singleton();
};

#endif // BRANCH_HPP
