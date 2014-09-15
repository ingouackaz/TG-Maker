
#include "Player.hpp"
#include "ProjectManager.hpp"
#include "Position.hpp"

Player::Player()
    : m_data(ProjectManager::singleton().meta().player), m_moved(true)
{
    apply_image(m_data.image.id, m_data.image.at_x, m_data.image.at_y);
    move(m_data.x, m_data.y, false);
}

void Player::move(int x, int y, bool make_valid)
{
    if (make_valid)
        PositionManager::make_valid(x, y);
    
    {
        PositionManager::const_iterator it(PositionManager::singleton().find(y * ProjectManagerBase::map_width + x));
        if (it != PositionManager::singleton().end())
        {
            m_data.x = x;
            m_data.y = y;
            SetPosition(x * ProjectManagerBase::tile_width, y * ProjectManagerBase::tile_height);
            m_moved = true;
        }
    }
}

void Player::apply_image(int id_image, int tile_at_x, int tile_at_y)
{
    if (id_image != -1)
    {
        m_data.image.id = id_image;
        m_data.image.at_x = tile_at_x;
        m_data.image.at_y = tile_at_y;

        SetImage(ImageManager::singleton().fetch(id_image));
        SetSubRect(sf::IntRect(
            tile_at_x                                   , tile_at_y,
            tile_at_x + ProjectManagerBase::tile_width  , tile_at_y + ProjectManagerBase::tile_height
        ));
    }
}

