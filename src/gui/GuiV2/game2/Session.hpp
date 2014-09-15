#ifndef SESSION_HPP
#define SESSION_HPP
#include "Game.hpp"
#define X_IMAGE         325.f
#define Y_IMAGE         230.f
#define X_TEXT          100.f
#define Y_TEXT          40.f

class	Session
{
public:
  virtual ~Session();
  virtual Session *update(Game &) = 0;
  virtual void draw(Game &) = 0;

protected:
    int                     _selected;
};

#endif
