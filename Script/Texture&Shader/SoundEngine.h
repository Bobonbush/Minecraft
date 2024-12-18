#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <iostream>
#include "Utils/Singleton.h"
#include <irrKlang.h>
using namespace irrklang;


class SoundEngine : Singleton {
    private:
        irrklang::ISoundEngine* engine;
        void Init();

        static SoundEngine * instance;
        SoundEngine();
    public:

        static SoundEngine * GetInstance() {
            if(instance == nullptr) {
                instance = new SoundEngine();
            }
            return instance;
        }
        
        ~SoundEngine();
        
        void PlaySound(const char* path);
        void PlaySound(const char* path, bool loop);
        void PlaySound(const char* path, bool loop, bool startPaused);
        void PlaySound(const char* path, bool loop, bool startPaused, bool track);
        void StopAllSounds();
        void Drop();
        void SetSoundVolume(float volume);
        void SetSoundPosition(float x, float y, float z);
        void StopSound(const char* path);

};

#endif // SOUNDENGINE_H