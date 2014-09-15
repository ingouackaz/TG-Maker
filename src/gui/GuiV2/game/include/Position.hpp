 
#ifndef HPP_POSITION
#define HPP_POSITION

#include <SFML/Graphics/Sprite.hpp>

#include "PositionBase.hpp"
#include "Image.hpp"
#include "ProjectManagerBase.hpp"

class Position : public PositionBase, public sf::Sprite
{
    public:
    virtual void load();
    
    void apply_image(int id_image, int tile_at_x, int tile_at_y);

    protected:
};

class PositionManager : public Manager<Position>
{
    public:
    static PositionManager& singleton();

    static void make_valid(int& x, int& y);

    private:
    PositionManager();
    PositionManager(PositionManager const& m);
};

#endif

