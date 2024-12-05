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
    public:
        SoundEngine();
        ~SoundEngine();
        
        void PlaySound(const char* path);
        void PlaySound(const char* path, bool loop);
        void PlaySound(const char* path, bool loop, bool startPaused);
        void PlaySound(const char* path, bool loop, bool startPaused, bool track);
        void StopAllSounds();
        void Drop();
        void SetSoundVolume(float volume);
        void SetSoundPosition(float x, float y, float z);

};

#endif // SOUNDENGINE_H