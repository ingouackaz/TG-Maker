
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Position.hpp"
#include "ProjectManager.hpp"
#include "Image.hpp"

void Position::load()
{
    apply_image(res_data.id_image, res_data.image_tile_at[0], res_data.image_tile_at[1]);
    SetPosition(res_data.x * ProjectManagerBase::tile_width, res_data.y * ProjectManagerBase::tile_height);
}

void Position::apply_image(int id_image, int tile_at_x, int tile_at_y)
{
    if (id_image != -1)
    {
        res_data.id_image = id_image;
        res_data.image_tile_at[0] = tile_at_x;
        res_data.image_tile_at[1] = tile_at_y;

        SetImage(ImageManager::singleton().fetch(id_image));
        SetSubRect(sf::IntRect(
                tile_at_x                                   , tile_at_y,
                tile_at_x + ProjectManagerBase::tile_width  , tile_at_y + ProjectManagerBase::tile_height
            ));
    }
}

void PositionManager::make_valid(int& x, int& y)
{
    if (x < 0)
        x = 0;
    if (x >= (int)ProjectManagerBase::map_width)
        x = ProjectManagerBase::map_width - 1;
    if (y < 0)
        y = 0;
    if (y >= (int)ProjectManagerBase::map_height)
        y = ProjectManagerBase::map_height;
}

PositionManager& PositionManager::singleton()
{
    static bool registered(false);
    static PositionManager singleton;

    if (!registered)
    {
        registered = true;
        ProjectManager::singleton().register_manager(&singleton);
    }

    return singleton;
}

PositionManager::PositionManager()
    : Manager<Position>(Position::manager_id)
{
}

