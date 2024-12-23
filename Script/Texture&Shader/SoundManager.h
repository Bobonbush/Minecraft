#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <iostream>
#include "Utils/Singleton.h"
#include <irrKlang.h>
#include <vector>
#include <map>
#include "Utils/Singleton.h"
#include <irrKlang.h>
using namespace irrklang;


class SoundManager : Singleton {
    private:
        irrklang::ISoundEngine* engine;

        std::map<std::string , std::string> soundMap; // Sound Name, Sound Path
        std::map<std::string , int > InUseSound;
        
        void AddTrack(const std::string & soundName, const std::string & path) {
            soundMap[soundName] = path;
        }
        void Init();

        static SoundManager * instance;
        std::vector<irrklang::ISound*> sounds;
        std::map<std::string , int> inTrack; 

        SoundManager();
    public:

        static SoundManager * GetInstance() {
            if(instance == nullptr) {
                instance = new SoundManager();
            }
            return instance;
        }
        
        ~SoundManager();
        
        void PlaySound(const char* path);
        void PlaySound(const char * path, float alpha);
        void PlaySound(const char* path, bool loop, float alpha);
        void PlaySound(const char* path, bool loop, bool startPaused);
        void PlaySound(const char* path, bool loop, bool startPaused, bool track);
        void PlaySoundEffect(const char* path);
        void StopAllSounds();
        void StopAllSoundsEffect();
        void Drop();
        void SetSoundVolume(float volume);
        void SetSoundPosition(float x, float y, float z);
        void StopSound(const char* path);
        
        void setVolume(float volume, const char* path);
};

#endif // SOUNDENGINE_H