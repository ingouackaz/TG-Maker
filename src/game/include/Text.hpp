
#ifndef HPP_TEXT
#define HPP_TEXT

#include <SFML/Graphics/String.hpp>

#include "TextBase.hpp"

class Text : public TextBase, public sf::String
{
    public:
    Text() : sf::String()
    {
    }

    virtual void load();
};

#include "Manager.hpp"
#include "BufferContainer.hpp"

class TextManager : public Manager<Text>
{
    public:
    static TextManager& singleton();

    virtual void load();

    private:
    TextManager();
    TextManager(TextManager const& m);

    BufferContainer<Text> m_buffers;
};

#endif

