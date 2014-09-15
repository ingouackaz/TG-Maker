
#ifndef HPP_PLAYER
#define HPP_PLAYER

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

#include "ProjectManagerBase.hpp"

class Player : public sf::Sprite
{
    public:
    Player();

    int x() const
    {
        return m_data.x;
    }

    int y() const
    {
        return m_data.y;
    }

    bool moved() const
    {
        return m_moved;
    }

    void move(int x, int y, bool make_valid=true);

    void set_moved(bool value)
    {
        m_moved = value;
    }

    void apply_image(int id_image, int tile_at_x, int tile_at_y);

    protected:
    ProjectManagerBase::PlayerData& m_data;
    bool m_moved;
};

#endif

