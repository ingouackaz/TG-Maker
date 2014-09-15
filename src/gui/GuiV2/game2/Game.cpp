#include "Game.hpp"
#include "Session.hpp"
#include "MenuSession.hpp"
#include <iostream>

Game::Game()
{
}

void Game::initialize()
{
    _app = new  sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML Events",4);

    if (_app == NULL)
    {
        _app = NULL;
        _session = NULL;
    }
    _app->SetFramerateLimit(30);
    _session = new MenuSession();
}

void Game::run()
{
    initialize();

    while (_app->IsOpened())
    {
        update();
        draw();
    }
}

void Game::draw()
{
    if (!_session)
        _app->Close();
    else
    {
        _app->Clear();
        _session->draw(*this);
        _app->Display();
    }
}



void Game::update()
{
    Session       *old = 0;

    if (!_session)
        _app->Close();
    else
    {
        old = _session;
        try{
            if ((_session = _session->update(*this)) != old)
                delete old;
        }
        catch (std::exception& e){
            std::cerr << e.what() << std::endl;
            _session = 0;
        }
    }
}
