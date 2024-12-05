#include "SoundEngine.h"

SoundEngine::SoundEngine() {
    Init();
}

SoundEngine::~SoundEngine() {
    Drop();
}

void SoundEngine::Init() {
    engine = createIrrKlangDevice();
    if(!engine) {
        std::cout << "Failed to initialize Sound Engine" << std::endl;
        return;
    }
}

void SoundEngine::PlaySound(const char* path) {
    engine -> play2D(path);
}

void SoundEngine::PlaySound(const char* path, bool loop) {
    engine -> play2D(path, loop);
}

void SoundEngine::PlaySound(const char* path, bool loop, bool startPaused) {
    engine -> play2D(path, loop, startPaused);
}

void SoundEngine::PlaySound(const char* path, bool loop, bool startPaused, bool track) {
    engine -> play2D(path, loop, startPaused, track);
}

void SoundEngine::StopAllSounds() {
    engine -> stopAllSounds();
}

void SoundEngine::Drop() {
    engine -> drop();
}

void SoundEngine::SetSoundVolume(float volume) {
    engine -> setSoundVolume(volume);
}



void SoundEngine::SetSoundPosition(float x, float y, float z) {
    engine -> setListenerPosition(vec3df(x, y, z), vec3df(0, 0, 1));
}


