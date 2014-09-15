#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio.hpp>

#include "Manager.hpp"
#include "SoundBase.hpp"

class Sound : public SoundBase, public sf::Music
{
public:
    Sound();
    Sound(const std::string &path);

public:
    std::string getPath() const
    {
        return std::string(res_data.path);
    }
    void setPath(const std::string &path)
    {
        strncpy(res_data.path, path.c_str(), sizeof(res_data.path));
        res_data.path[sizeof(res_data.path) - 1] = 0;
    }

    void load();
};

class SoundManager : public Manager<Sound>
{
private:
    SoundManager();

public:
    static SoundManager &singleton();

public:
    static void loadDefault();
    static void copyResources();
};

#endif // SOUND_HPP
