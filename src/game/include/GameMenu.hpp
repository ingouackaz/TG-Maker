
#ifndef HPP_GAMEMENU
#define HPP_GAMEMENU

#include "IGameTask.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <iostream>
#include <vector>

#define IMAGE_MENU      "resources/image_menu.jpg"
#define X_IMAGE         375
#define Y_IMAGE         410
#define OFFSET          45

class GameRunner;

class GameMenu : public IGameTask
{
    public:
    enum GameMenuOptions
    {
        Play,
        LoadGame,
        SaveGame,
        Exit,
        GameMenuOptionsTotal,
    };
    
    GameMenu();
    GameMenu(GameRunner* gr);

    // IGameTask implementation
    virtual float interval() const;
    virtual void handle_event(Game& game, sf::Event const& event);
    virtual void execute(Game& game);
    virtual void draw(Game& game);

    protected:
    void _init();
    static unsigned int const menu_image_png_size;
    static unsigned char const menu_image_png[];

    sf::Image _imageMenu;
    sf::Sprite _spriteMenu;
    sf::String _text[GameMenuOptionsTotal];
    int m_selected;
    GameRunner* m_current_game;
};

#endif

