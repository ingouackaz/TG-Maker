
#ifndef HPP_SOUND
#define HPP_SOUND

#include <SFML/Audio.hpp>

#include "SoundBase.hpp"

class Sound : public SoundBase, public sf::SoundBuffer, public sf::Sound
{
    public:
    virtual void load()
    {
    }

    protected:
    char const* m_buffer;
};

#include "Manager.hpp"
#include "BufferContainer.hpp"

class SoundManager : public Manager<Sound>
{
    public:
    static SoundManager& singleton();

    virtual void load();

    BufferContainer<Sound> const& buffers() const
    {
        return m_buffers;
    }

    BufferContainer<Sound>& buffers()
    {
        return m_buffers;
    }

    private:
    SoundManager();
    SoundManager(SoundManager const& m);

    BufferContainer<Sound> m_buffers;
};

#endif

