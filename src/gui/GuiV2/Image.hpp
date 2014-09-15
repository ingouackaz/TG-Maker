#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SFML/Graphics/Image.hpp>

#include "ImageBase.hpp"
#include "Manager.hpp"

class Image : public ImageBase, public sf::Image
{
public:
    Image();
    Image(const std::string &path);

public:
    std::string getFileName()
    {
        return std::string(res_data.path);
    }
    std::string getPath() const
    {
        return std::string(res_data.path);
    }
    void setPath(const std::string &path)
    {
        strncpy(res_data.path, path.c_str(), sizeof(res_data.path));
        res_data.path[sizeof(res_data.path) - 1] = 0;
    }

public:
    void load();

};

class ImageManager : public Manager<Image>
{
private:
    ImageManager();

public:
    static ImageManager &singleton();

public:
    static void copyResources();
    static void loadDefault();

};

#endif // IMAGE_HPP
