
#include "Position.hpp"
#include "ProjectManager.hpp"
#include "LoadingBarDialog.hpp"

Position::Position()
{

}

Position::Position(int mapX, int mapY, int tilesetId, int tilesetX, int tilesetY)
{
    setMapX(mapX);
    setMapY(mapY);
    setTilesetId(tilesetId);
    setTilesetX(tilesetX);
    setTilesetY(tilesetY);
    res_data.flags = 0;
    //    if (rand() % 2)
    //        setCollision(true);
    res_data.state = 0;
    res_data.id_event = -1;
    res_data.event_delay = -1;
}

PositionManager& PositionManager::singleton()
{
    static bool registered(false);
    static PositionManager singleton;


    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);
        registered = true;
    }

    return singleton;
}

PositionManager::PositionManager()
    : Manager<Position>(Position::manager_id)
{

}

void PositionManager::loadDefault()
{
    for (int x = 0; x < ProjectManagerBase::map_width; ++x)
    {
        LoadingBarDialog::mutex.lock();
        LoadingBarDialog::loadingValue = ProjectManagerBase::map_width * x / 100;
        LoadingBarDialog::mutex.unlock();
        for (int y = 0; y < ProjectManagerBase::map_height; ++y)
        {
            //            PositionManager::singleton().push(new Position(x, y, 0, 1, 1));
            PositionManager::singleton().push(new Position(x, y, 0, 1, 1));
        }
    }
    LoadingBarDialog::loadingValue = 100;
}
