#include "RectSelection.hpp"

void RectSelection::setOrigin(mapCase & mapcase, const std::string & im)
{
    if (mapcase.first < 0)
        mapcase.first *= -1;
    if (mapcase.second < 0)
        mapcase.second *= -1;
    _origin = mapcase;
    _im = im;
    std::cout << "X = "<< mapcase.first << "\n Y = " << mapcase.second << std::endl;
}

void RectSelection::setLargeur(int largeur)
{
    int tmp;

    tmp = 0;
    _largeur = largeur + tmp;
}

void RectSelection::setHauteur(int hauteur)
{
    int tmp;

    tmp = 0;
    _hauteur = hauteur + tmp;
}

mapCase RectSelection::getOrigin() const
{
    return (_origin);
}

int RectSelection::getLargeur() const
{
    return (_largeur);
}

int RectSelection::getHauteur() const
{
    return (_hauteur);
}

const std::string &RectSelection::getImage() const
{
    return (_im);
}

RectSelection::RectSelection()
    : _largeur(0), _hauteur(0)
{
    _origin.first = 0;
    _origin.second = 0;
}

RectSelection::~RectSelection()
{
}

