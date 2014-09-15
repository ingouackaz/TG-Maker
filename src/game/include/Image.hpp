
#ifndef HPP_IMAGE
#define HPP_IMAGE

#include <SFML/Graphics/Image.hpp>

#include "ImageBase.hpp"

class Image : public ImageBase, public sf::Image
{
    public:
    Image() : sf::Image()
    {
    }

    virtual void load()
    {
    }
};

#include "Manager.hpp"
#include "BufferContainer.hpp"

class ImageManager : public Manager<Image>
{
    public:
    static ImageManager& singleton();

    virtual void load();

    BufferContainer<Image> const& buffers() const
    {
        return m_buffers;
    }

    BufferContainer<Image>& buffers()
    {
        return m_buffers;
    }

    private:
    ImageManager();
    ImageManager(ImageManager const& m);

    BufferContainer<Image> m_buffers;
};

#endif

