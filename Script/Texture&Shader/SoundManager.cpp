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
    AddTrack("ItemBreak", "Assets/SoundEffect/ItemBreak.wav");
    AddTrack("Jumping", "Assets/SoundEffect/Jumping.wav");
    AddTrack("Falling", "Assets/SoundEffect/Falling.wav");
    AddTrack("Hurt", "Assets/SoundEffect/Hurt.wav");
}

void SoundManager::PlaySound(const char* path) {
    engine -> play2D(soundMap[path].c_str());
}

void SoundManager::PlaySound(const char * path, float alpha) {
    engine -> play2D(soundMap[path].c_str(), false, false, true) -> setVolume(alpha);
}

void SoundManager::PlaySoundEffect(const char* path) {
    if(inTrack.find(path) != inTrack.end()) {
        return ;
    }

    bool enableSoundEffects = true;





    sounds.push_back(engine -> play2D(soundMap[path].c_str(), true, false, true));

    inTrack[path] = (int) sounds.size() - 1;
}
void SoundManager::PlaySound(const char* path, bool loop, float alpha) {
    if(InUseSound.find(path) != InUseSound.end()) {
        return ;
    }

    InUseSound[path] = 1;
    irrklang::ISound * sound = engine -> play2D(soundMap[path].c_str(), loop, false , true);
    if(sound) {
        sound -> setVolume(alpha);   // BackGround Sound
    }


}

void SoundManager::PlaySound(const char* path, bool loop, bool startPaused) {

    engine -> play2D(soundMap[path].c_str(), loop, startPaused);

}

void SoundManager::PlaySound(const char* path, bool loop, bool startPaused, bool track) {

    engine -> play2D(soundMap[path].c_str(), loop, startPaused, track);
    
}

void SoundManager::StopAllSounds() {
    engine -> stopAllSounds();
    sounds.clear();
    inTrack.clear();
    InUseSound.clear();
}

void SoundManager::StopAllSoundsEffect() {
    for(auto & sound : sounds) {
        sound -> stop();
        sound -> drop();
    }
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
        if( t >= (int) sounds.size()) {
            StopAllSoundsEffect();
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
        if(t >= (int) sounds.size()) {
            StopAllSoundsEffect();
            return ;
        }
        if(sounds[inTrack[path]])
            sounds[inTrack[path]] -> setVolume(volume);
    }
}

