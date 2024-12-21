#include "SoundManager.h"


SoundManager * SoundManager::instance = nullptr;
SoundManager::SoundManager() {
    Init();
}

SoundManager::~SoundManager() {
    delete instance;
    for(auto & sound : sounds) {
        sound -> stop();
        sound -> drop();
    }
    Drop();
}

void SoundManager::Init() {
    engine = createIrrKlangDevice();
    if(!engine) {
        std::cout << "Failed to initialize Sound Engine" << std::endl;
        return;
    }

    AddTrack("Menu", "Assets/Music/Opening.wav");
    AddTrack("Hover", "Assets/SoundEffect/hover.wav");
    AddTrack("Step", "Assets/SoundEffect/step.wav");
    AddTrack("WaterStep", "Assets/SoundEffect/waterStep.wav");
    AddTrack("Death", "Assets/Music/death.wav");
    AddTrack("Block", "Assets/SoundEffect/stone.wav");
    AddTrack("Breaking", "Assets/SoundEffect/Breaking.wav");
    AddTrack("Background", "Assets/Music/Background.wav");
}

void SoundManager::PlaySound(const char* path) {


    engine -> play2D(soundMap[path].c_str());
    
    //sounds.push_back(engine -> play2D(soundMap[path].c_str()));
    //inTrack[path] = (int) sounds.size() - 1;

    
    
}

void SoundManager::PlaySoundEffect(const char* path) {
    if(inTrack.find(path) != inTrack.end()) {
        return ;
    }

    bool enableSoundEffects = true;





    sounds.push_back(engine -> play2D(soundMap[path].c_str(), true, false, true));

    inTrack[path] = (int) sounds.size() - 1;
}
void SoundManager::PlaySound(const char* path, bool loop) {
    if(inTrack.find(path) != inTrack.end()) {
        return ;
    }
    irrklang::ISound * sound = engine -> play2D(soundMap[path].c_str(), loop);
    sounds.push_back(sound);
    inTrack[path] = (int) sounds.size() - 1;


}

void SoundManager::PlaySound(const char* path, bool loop, bool startPaused) {
    if(inTrack.find(path) != inTrack.end()) {
        return ;
    }

    sounds.push_back(engine -> play2D(soundMap[path].c_str(), loop, startPaused));
    inTrack[path] = (int) sounds.size() - 1;
}

void SoundManager::PlaySound(const char* path, bool loop, bool startPaused, bool track) {
    if(inTrack.find(path) != inTrack.end()) {
        return ;
    }
    sounds.push_back(engine -> play2D(soundMap[path].c_str(), loop, startPaused, track));
    inTrack[path] = (int) sounds.size() - 1;
}

void SoundManager::StopAllSounds() {
    engine -> stopAllSounds();
    sounds.clear();
    inTrack.clear();
}

void SoundManager::Drop() {
    engine -> drop();


}

void SoundManager::SetSoundVolume(float volume) {
    engine -> setSoundVolume(volume);

}



void SoundManager::SetSoundPosition(float x, float y, float z) {
    engine -> setListenerPosition(vec3df(x, y, z), vec3df(0, 0, 1));
}

void SoundManager::StopSound(const char* path) {
    if(inTrack.find(path) != inTrack.end()) {
        int t = inTrack[path];
        if(t > sounds.size()) {
            SoundManager::GetInstance() -> StopAllSounds();
            return ;
        }
        if(sounds[t]) {

        
            sounds[t] -> stop();
            sounds[t] -> drop();
        }

        sounds.erase(sounds.begin() + inTrack[path]);
        inTrack.erase(path);
    }
}

void SoundManager::setVolume(float volume, const char* path) {
    if(inTrack.find(path) != inTrack.end()) {
        int t = inTrack[path];
        if(t > sounds.size()) {
            SoundManager::GetInstance() -> StopAllSounds();
            return ;
        }
        if(sounds[inTrack[path]])
            sounds[inTrack[path]] -> setVolume(volume);
    }
}

