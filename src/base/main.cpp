
// ProjectManager.hpp example
#include "ProjectManagerBase.hpp"

class ProjectManager : public ProjectManagerBase
{
    public:
    protected:
};

// Position.hpp example
#include <string>

#include "PositionBase.hpp"
#include "Manager.hpp"

class Position : public PositionBase
{
    public:
    Position()
    {
        res_data.x = -1;
        res_data.y = -1;
    }
    
    Position(int x, int y)
    {
        res_data.x = x;
        res_data.y = y;
    }

    virtual void load()
    {
        std::cout << "loaded, position is " << res_data.x << ' ' << res_data.y << std::endl;
    }

    protected:
};

class PositionManager : public Manager<Position>
{
    public:
    PositionManager()
        : Manager<Position>("POS")
    {
    }
};

// Image.hpp example
#include <string>

#include "ImageBase.hpp"
#include "Manager.hpp"

class Image : public ImageBase
{
    public:
    Image()
    {
        *res_data.path = '\0';
    }

    Image(std::string const& path)
        : m_path(path)
    {
        strcpy(res_data.path, path.c_str());
    }

    virtual void load()
    {
        m_path = this->res_data.path;
        std::cout << "loaded, image file is " << m_path << std::endl;
    }

    std::string const& get_path() const
    {
        return m_path;
    }

    protected:
    std::string m_path;
};

class ImageManager : public Manager<Image>
{
    public:
    ImageManager()
        : Manager<Image>("IMG")
    {
    }
};

// main.cpp example
#include <iostream>

int main(int ac, char **av)
{
    bool serialize(ac == 2 && *av[1] == 's');
    std::string save("gamesave.bin");

    // le plus important a spawn : le managermanager
    // (je garde une ref dessus pour pas avoir a appeler singelon() tout le temps,
    // t'est pas oblige de le faire)

    ProjectManager promgr;

    // la je spawn la liste des managers que je veux utiliser
    // (bon la y en a qu'un mais faut rajouter sound, tile, ...)

    ImageManager imgr;
    PositionManager pmgr;
    //...

    // les register
    promgr.register_manager(&imgr);
    promgr.register_manager(&pmgr);


    if (serialize)
    {
        // je rajoute des elements dans mes managers
        // ces elements sont a construire par vous, on fournit les boites vides 
        // rajoutez les methodes, attributs et constructeurs que vous voulez dedans

        promgr.set_name("super aventure");
        promgr.set_author("bguina");
        promgr.meta().player.x = 42;
        promgr.meta().player.y = 3411;

        imgr.push(new Image("bob.bmp"));
        imgr.push(new Image("dad.bmp"));
        pmgr.push(new Position(22, 44));
        pmgr.push(new Position(88, 44));

        // je peux iterer dessus facilement

        for (ImageManager::const_iterator it = imgr.begin(); it != imgr.end(); ++it)
        {
            (void)it;
            // traitement
        }

        // ou simplement faire acceder a des donnees directement,
        // on garde en tete que les structures de donnees sont des map avec des int en cle
        // (les cles sont generees automatiquement par defaut)

        imgr.find(0); // renvoit le const_iterator
        imgr[0]; // fait le find et renvoit direct la value


        // et voila tout marche bien, donc on veut sauvegarder tout ca
        // la serial/deserial se fait grace au ProjectManager
    
        std::cout << "serialize: " << ((promgr.serialize(save)) ? "success" : "failed") << std::endl;
    }
    else
    {

        // HOP programme termine, on va dire pour le tuto que en dessous c'est un nouveau binaire
        // on reinstancie les managers (je le refais pas, c'est pas vraiment un binaire different,
        // attention, faut suivre)
        // a noter que le deserialize vide les managers avant de deserialiser, previens le user ou un truc du style
        // quand tu ouvres un projet tu perds les donnees courantes. (si ca fait vraiment chier je ferai la fusion de managers)
        // mais ca va etre casse couille sur les id uniques et je pense pas qu'il y ait besoin

        ///////////////////////////////////
        //      WARNING WARNING WARNING
        // instanciez tous les managers AVANT de deserialiser, sinon il ne connaitra pas le manager
        // manquant et foutra les donnees inconnues a la poubelle !!
        ///////////////////////////////////

        std::cout << "deserialize\n";
        
        try
        {
            promgr.deserialize(save);
        }
        catch (std::runtime_error const& e)
        {
            std::cout << "    failed: " << e.what() << std::endl;
        }

        std::cout << "name = " << promgr.name() << std::endl;
        std::cout << "author = " << promgr.author() << std::endl;
        std::cout << "player start = " << promgr.meta().player.x << ',' << promgr.meta().player.y << std::endl;
        
        for (ImageManager::const_iterator it = imgr.begin(); it != imgr.end(); ++it)
            std::cout << "Images[" << it->first << "] = " << it->second->get_path() << std::endl;
        
        for (PositionManager::const_iterator it = pmgr.begin(); it != pmgr.end(); ++it)
            std::cout << "Positions[" << it->first << "] = " << it->second->res_data.x << ' ' << it->second->res_data.y << std::endl;
         
        // et la vous avez recupere vos donnes
        // un petit ' hexdump -C gamesave.bin ' pour voir comme c'est beau

    }

    return 0;
}

