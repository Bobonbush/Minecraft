#include "SoundManager.h"

SoundManager * SoundManager::instance = nullptr;


SoundManager::SoundManager() {
    soundEngine = SoundEngine::GetInstance();
    AddTrack("Menu", "Assets/Music/Opening.mp3");
    AddTrack("Hover", "Assets/SoundEffect/hover.mp3");
    AddTrack("Step", "Assets/SoundEffect/step.mp3");
    AddTrack("WaterStep", "Assets/SoundEffect/waterStep.mp3");
    AddTrack("Death", "Assets/Music/death.mp3");
}

void SoundManager::PlaySound(const std::string & soundName) {
    soundEngine -> PlaySound(soundMap[soundName].c_str());
}

void SoundManager::PlaySound(const std::string & soundName, bool loop) {
    soundEngine -> PlaySound(soundMap[soundName].c_str(), loop);
}

void SoundManager::PlaySound(const std::string & soundName, bool loop, bool startPaused) {
    soundEngine -> PlaySound(soundMap[soundName].c_str(), loop, startPaused);
}

void SoundManager::PlaySound(const std::string & soundName, bool loop, bool startPaused, bool track) {
    soundEngine -> PlaySound(soundMap[soundName].c_str(), loop, startPaused, track);
}

void SoundManager::StopAllSounds() {
    soundEngine -> StopAllSounds();
}