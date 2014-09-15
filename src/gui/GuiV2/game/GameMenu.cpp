
#include <SFML/Window/Event.hpp>
#include <string>

#include "GameMenu.hpp"
#include "GameRunner.hpp"
#include "Game.hpp"


GameMenu::GameMenu()
    : m_selected(GameMenu::Play), m_current_game(0)
{
    _init();
}

GameMenu::GameMenu(GameRunner* gr)
    : m_selected(GameMenu::Play), m_current_game(gr)
{
    gr->pause();
    _init();
}

void GameMenu::_init()
{
  if (!_imageMenu.LoadFromMemory(reinterpret_cast<char const*>(menu_image_png), menu_image_png_size))
    std::cout << "image loading failed" << std::endl;
  _spriteMenu.SetImage(_imageMenu);
  
  _text[Play].SetText("Play");
  _text[LoadGame].SetText("Load");
  _text[SaveGame].SetText("Save");
  _text[Exit].SetText("Exit");
  for(int i = 0; i < GameMenuOptionsTotal; ++i)
  {
    _text[i].SetSize(22);
    _text[i].SetPosition(X_IMAGE, Y_IMAGE + ( OFFSET * i ));
  }
}

float GameMenu::interval() const
{
  return .0f;
}

void GameMenu::handle_event(Game& game, sf::Event const& event)
{
    ProjectManager& promgr(ProjectManager::singleton());

    //game.EnableKeyRepeat(false);
    switch (event.Type)
    {
        case sf::Event::KeyPressed:
            switch (event.Key.Code)
            {
                case sf::Key::Down:
                    if (m_selected < GameMenuOptionsTotal - 1)
                        ++m_selected;
                    else
                        m_selected = Play;
                    break;

                case sf::Key::Up:
                    if (m_selected > 0)
                        --m_selected;
                    else
                        m_selected = GameMenuOptionsTotal - 1;
                    break;

                case sf::Key::Return:
                    switch (m_selected)
                    {
                        case Play:
                            {
                                GameRunner* gr(new GameRunner);

                                game.switch_task(gr);
                                gr->resume();
                            }
                            break;
                        case LoadGame:
                            try
                            {
                                promgr.deserialize(std::string("gamesave.bin"));
                            }
                            catch (std::runtime_error const& e)
                            {
                                std::cerr << "Cannot load gamesave.bin: " << e.what() << std::endl;
                            }
                            break;
                        case SaveGame:
                            if (!promgr.serialize("gamesave.bin"))
                            {
                                std::cerr << "Error writing gamesave.bin." << std::endl;
                            }
                            break;
                        case Exit:
                            game.switch_task(0);
                            break;
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            break;

        case sf::Event::Closed:
            game.switch_task(0);
            break;

        default:
            break;
    }
}

void GameMenu::execute(Game& game)
{
  (void)game;
}

void GameMenu::draw(Game& game)
{    
  // afficher des trucs  
  game.Draw(_spriteMenu);
  for(int i = 0; i < GameMenuOptionsTotal; ++i)
  {
    if (m_selected == i)
      _text[i].SetColor(sf::Color(255, 210, 0));
    else
      _text[i].SetColor(sf::Color(255, 255, 255));
    game.Draw(_text[i]);    
  }
}

