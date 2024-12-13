#include "timer.h"


Timer::Timer(float maxTime) : maxTime(maxTime) {
    efficiency = 0;
    this -> maxTime *= 0.35f;
}

Timer::Timer(float maxTime, float efficiency) : maxTime(maxTime), efficiency(efficiency) {
    this -> efficiency++;
    this -> maxTime *= 0.35f;
}

void Timer::Update(float deltaTime) {
    currentTime += deltaTime * efficiency;

}

void Timer::Reset() {
    currentTime = 0.f;
}

bool Timer::isFinished() {
    return currentTime >= maxTime;
}

const int Timer::getInUse() const {
    return inUse;
}

void Timer::setInUse(int id) {
    inUse = id;
}

const glm::vec3 & Timer::getBlockPosition() {
    return blockPosition;
}

void Timer::setBlockPosition(const glm::vec3 & position) {
    blockPosition = position;
}

const float Timer::getCurrentTime() const {
    return currentTime;
}

const float Timer::getMaxTime() const {
    return maxTime;
}