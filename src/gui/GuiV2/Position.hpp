#ifndef POSITION_HPP
#define POSITION_HPP

 #include <QMutex>

#include "Manager.hpp"
#include "PositionBase.hpp"
#include "ProjectManagerBase.hpp"

class Position : public PositionBase
{
public:
    Position();

    Position(int mapX, int mapY, int tilesetId, int tilesetX, int tilesetY);

public:
    int getMapX() const
    {
        return res_data.x;
    }
    void setMapX(int posX)
    {
        res_data.x = posX;
    }
    int getMapY() const
    {
        return res_data.y;
    }
    void setMapY(int posY)
    {
        res_data.y = posY;
    }
    int getTilesetId() const
    {
        return res_data.id_image;
    }
    void setTilesetId(int tilesetId)
    {
        res_data.id_image = tilesetId;
    }
    int getTilesetX() const
    {
        return res_data.image_tile_at[0];
    }
    void setTilesetX(int tilesetX)
    {
        res_data.image_tile_at[0] = tilesetX;
    }
    int getTilesetY() const
    {
        return res_data.image_tile_at[1];
    }
    void setTilesetY(int tilesetY)
    {
        res_data.image_tile_at[1] = tilesetY;
    }
    bool getCollision() const
    {
        return (res_data.flags & PositionBase::IsCollidable);
    }
    void setCollision(bool collision)
    {
        if (collision)
            res_data.flags |= PositionBase::IsCollidable;
        else
            res_data.flags &= !PositionBase::IsCollidable;
    }

public:
    void load()
    {

    }
};

class PositionManager : public Manager<Position>
{
private:
    PositionManager();

public:
    static PositionManager &singleton();

public:
    Position *getPosition(int x, int y)
    {
        //                std::cout << "returning  " << x + y * ProjectManagerBase::map_width << "got asked [" << x << ";" << y << "]" << std::endl;
        return (*this)[x + y * ProjectManagerBase::map_width];
    }

    static void loadDefault();
};

#endif // POSITION_HPP
