#ifndef ACTION_HPP
#define ACTION_HPP

#include <QTreeWidget>

#include "Manager.hpp"
#include "ActionBase.hpp"

class Action : public ActionBase , public QTreeWidgetItem
{
public:
    Action();

    void set_Action(ActionType type, int id_target);
    void set_Action(ActionType type, int a, int b);
    void set_Action(ActionType type, int id_image, int tile_at_x, int tile_at_y);
    void set_Action(ActionType type, int x, int y, int id_image, int tile_at_x, int tile_at_y);

    virtual void load()
    {

    }

    std::string to_str() const;
};

class ActionManager : public Manager<Action>
{
private:
    ActionManager();

public:
    static ActionManager &singleton();
};

#endif // ACTION_HPP
