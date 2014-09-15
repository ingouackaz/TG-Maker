
class Action : public ActionBase, public Qt::QTreeViewItem
{

};

bool add_new_item_in(item)
{
    if (dynamic_cast<Action*>(item))
    {
        return false;
    }

    // ajouter l'item dans l'item

    return true;
}

