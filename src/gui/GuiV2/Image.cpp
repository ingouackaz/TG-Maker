#include <QFile>

#include "Image.hpp"
#include "ProjectManager.hpp"

Image::Image()
{

}

Image::Image(const std::string &path)
{
    LoadFromFile(ProjectManager::singleton().getProjectPath().toStdString() + "res/img/" + path);
    setPath(path.c_str());

    SetSmooth(false);
}

void Image::load()
{
    LoadFromFile(ProjectManager::singleton().getProjectPath().toStdString() + "res/img/" + res_data.path);

    SetSmooth(false);
}

ImageManager &ImageManager::singleton()
{
    static bool registered(false);
    static ImageManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);

        registered = true;
    }

    return singleton;
}

ImageManager::ImageManager()
    : Manager<Image>(Image::manager_id)
{

}

void    ImageManager::loadDefault()
{
    ImageManager::singleton().push(new Image("official_tileset.png"));
    ImageManager::singleton().push(new Image("pokemon2_tileset.png"));
    //    ImageManager::singleton().push(new Image("pokemon4_tileset.png"));
}

void    ImageManager::copyResources()
{
    QFile::copy("../resources/tilesets/official_tileset.png", ProjectManager::singleton().getProjectPath() + "res/img/official_tileset.png");
    QFile::copy("../resources/tilesets/pokemon2_tileset.png", ProjectManager::singleton().getProjectPath() + "res/img/pokemon2_tileset.png");
    //QFile::copy("../resources/tilesets/pokemon4_tileset.png", ProjectManager::singleton().getProjectPath() + "res/img/pokemon4_tileset.png");
}
