
#include <SFML/Window/Event.hpp>

#include "GameRunner.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Event.hpp"
#include "Position.hpp"
#include "Text.hpp"
#include "GameMenu.hpp"
#include "GameRunner.hpp"

float const GameRunner::interval_time = .200f;

GameRunner::GameRunner()
{
}

float GameRunner::interval() const
{
    return GameRunner::interval_time;
}

void GameRunner::handle_event(Game& game, sf::Event const& event)
{
    switch (event.Type)
    {
        case sf::Event::Closed:
            game.switch_task(0);
            break;

        case sf::Event::KeyPressed:
            switch (event.Key.Code)
            {
                case sf::Key::Escape:
                    game.switch_task(new GameMenu(this));
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void GameRunner::execute(Game& game)
{
    Player& player(ProjectManager::singleton().player());
    EventManager& emgr(EventManager::singleton());

    (void)game;

    // Process queued events
    emgr.tick();

    // Queue the position's event if the player moved
    if (player.moved())
    {
        PositionManager& pmgr(PositionManager::singleton());
        int pos_id(player.y() * ProjectManagerBase::map_width + player.x());
        PositionManager::const_iterator pos_it(pmgr.find(pos_id));
        
        if (pos_it != pmgr.end())
            emgr.queue(pos_it->second->res_data.id_event, pos_it->second->res_data.event_delay);
    }
}

void GameRunner::draw(Game& game)
{
    Player& player(ProjectManager::singleton().player());
    sf::Vector2f Center((player.x() + .5f) * ProjectManagerBase::tile_width, (player.y() + .5f) * ProjectManagerBase::tile_height);
    sf::Vector2f HalfSize(400, 300);
    sf::View View(Center, HalfSize);

    game.SetView(View);

    // Draw the tiles
    if (true){
        PositionManager& pmgr(PositionManager::singleton());
        int boundaries[2][2];

        boundaries[0][0] = player.x() - (ProjectManagerBase::screen_width / (2 * ProjectManagerBase::tile_width));
        boundaries[0][1] = player.y() - (ProjectManagerBase::screen_height / (2 * ProjectManagerBase::tile_height));
        boundaries[1][0] = player.x() + (ProjectManagerBase::screen_width / (2 * ProjectManagerBase::tile_width)) + 1;
        boundaries[1][1] = player.y() + (ProjectManagerBase::screen_height / (2 * ProjectManagerBase::tile_height)) + 1;
        PositionManager::make_valid(boundaries[0][0], boundaries[0][1]);
        PositionManager::make_valid(boundaries[1][0], boundaries[1][1]);

        //debug("draw boundaries: " << boundaries[0][0] << ' ' << boundaries[0][1] << ' ' << boundaries[1][0] << ' ' << boundaries[1][1] << std::endl);

        for (int y = boundaries[0][1]; y <= boundaries[1][1]; ++y)
        {
            for (int x = boundaries[0][0]; x <= boundaries[1][0]; ++x)
            {
                PositionManager::const_iterator it(pmgr.find(y * ProjectManagerBase::map_width + x));
               
                if (it != pmgr.end())
                {
                    //debug("draw " << it->second->res_data.x << ' ' << it->second->res_data.y << " at " << it->second->GetPosition().x << ' ' << it->second->GetPosition().y << "\n");
                    game.Draw(*it->second);
                }
            }
            //debug("\n");
        }
    }

    // Draw the player
    {
        game.Draw(player);
    }

    // Draw the texts
    {
        TextManager& tmgr(TextManager::singleton());

        for (TextManager::const_iterator it(tmgr.begin()); it != tmgr.end(); ++it)
            game.Draw(*it->second);
    }

    game.SetView(game.GetDefaultView());
}

void GameRunner::pause()
{
    EventManager::singleton().pause();
}

void GameRunner::resume()
{
    EventManager::singleton().resume();
}
