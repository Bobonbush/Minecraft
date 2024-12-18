#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "SoundEngine.h"
#include "Utils/Singleton.h"
#include <map>

class SoundManager : public Singleton {
    std::map<std::string , std::string> soundMap; // Sound Name, Sound Path
    SoundEngine * soundEngine;
    SoundManager();
    void AddTrack(const std::string & soundName, const std::string & path) {
        soundMap[soundName] = path;
    }
    static SoundManager * instance;
    public :

    static SoundManager * GetInstance() {
        if(instance == nullptr) {
            instance = new SoundManager();
        }
        return instance;
    }
    
    
    void PlaySound(const std::string & soundName);
    void PlaySound(const std::string & soundName, bool loop);
    void PlaySound(const std::string & soundName, bool loop, bool startPaused);
    void PlaySound(const std::string & soundName, bool loop, bool startPaused, bool track);
    void StopAllSounds();
};

#endif // SOUNDMANAGER_H