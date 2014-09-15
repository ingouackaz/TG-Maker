#include "Sound.hpp"
#include "ProjectManager.hpp"

Sound::Sound()
{

}

Sound::Sound(const std::string &path)
{
    OpenFromFile(ProjectManager::singleton().getProjectPath().toStdString() + "res/snd/" + path);
    Initialize(GetChannelsCount(), GetSampleRate());
    setPath(path.c_str());
}

void Sound::load()
{
    OpenFromFile(ProjectManager::singleton().getProjectPath().toStdString() + "res/snd/" + res_data.path);
    Initialize(GetChannelsCount(), GetSampleRate());
}


SoundManager::SoundManager()
    : Manager<Sound>(Sound::manager_id)
{


}

SoundManager &SoundManager::singleton()
{
    static bool registered(false);
    static SoundManager singleton;

    if (!registered)
    {
        ProjectManager::singleton().register_manager(&singleton);

        registered = true;
    }

    return singleton;
}

void    SoundManager::loadDefault()
{
    SoundManager::singleton().push(new Sound("blast.wav"));
    SoundManager::singleton().push(new Sound("tilt.wav"));
    SoundManager::singleton().push(new Sound("upgrade.wav"));
}

void    SoundManager::copyResources()
{
    QFile::copy("../resources/snd/blast.wav", ProjectManager::singleton().getProjectPath() + "res/snd/blast.wav");
    QFile::copy("../resources/snd/tilt.wav", ProjectManager::singleton().getProjectPath() + "res/snd/tilt.wav");
    QFile::copy("../resources/snd/upgrade.wav", ProjectManager::singleton().getProjectPath() + "res/snd/upgrade.wav");
}
