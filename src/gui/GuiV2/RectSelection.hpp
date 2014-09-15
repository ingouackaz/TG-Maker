#ifndef __RectMenu__
#define __RectMenu__

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "QSFMLCanvas.hpp"
#include <Qt/qapplication.h>
#include <Qt/qframe.h>
#include <Qt/qlabel.h>
#include <Qt/qevent.h>
#include <map>

typedef std::pair<int, int> mapCase;

class RectSelection
{
private:
    std::string   _im;
    mapCase	_origin;
    int		_largeur;
    int		_hauteur;

public:
    RectSelection();
    ~RectSelection();

public:
    void setOrigin(mapCase &, const std::string &);
    void setLargeur(int largeur);
    void setHauteur(int hauteur);

    mapCase getOrigin() const;
    int getLargeur() const;
    int getHauteur() const;
    const std::string &getImage() const;
};

#endif
