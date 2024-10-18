#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <Utils/Texture.h>
#include <Settings.h>

// SPA : SUPPORT FOR ALGORITHMS
class SPA {
    public :
    template<class X > static bool isSame(X a , X b) {
        return a == b;
    }

    template<class X > static bool isNotSame(X a , X b) {
        return a != b;
    }

    template<class X > static void clamp (X & a, X min, X max) {
        if (a < min) {
            a = min;
        } else if (a > max) {
            a = max;
        }
    } 

    static void ConvertToNDC(glm::vec3 &position) {
        Setting* setting = Setting::getInstance();
        position.x = (position.x / setting->getResolution().x) * 2 - 1;
        position.y = (position.y / setting -> getResolution().y) * 2 - 1;
    }


    static void SetSeed(int seed) {
        srand(seed);
    }

    static int RandomInt(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    static float RandomFloat(float min, float max) {
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }

    static void convertToLowerCase(std::string &str) {
        for (int i = 0; i < (int)str.size(); i++) {
            str[i] = tolower(str[i]);
        }
    }

};

#endif