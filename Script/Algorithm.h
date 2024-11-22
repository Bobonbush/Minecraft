#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <Utils/Texture.h>

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

    template<class X> static void RotateArray2f(std::vector<X> & arr, int cnt) {
        while(cnt--) {
            for(int i = 0; i < (int) arr.size() - 2; i+= 2) {
                std::swap(arr[i], arr[i + 2]);
                std::swap(arr[i + 1] , arr[i +3]);
            }
        }
    }

    template<class X> static void swap(X & a, X & b) {
        X temp = a;
        a = b;
        b = temp;
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

    template<class X> static X min(X a, X b) {
        return a < b ? a : b;
    }

    template<class X> static X max(X a, X b) {
        return a > b ? a : b;
    }

    template<class X> static X abs(X a) {
        return a < 0 ? -a : a;
    }

    template<class X> static X lerp(X a, X b, float t) {
        return a + t * (b - a);
    }

    template<class X> static X mix (X a, X b, float t) {
        return lerp(a, b, t);
    }

    template<class X> static X smoothstep(X a, X b, float t) {
        t = t * t * (3 - 2 * t);
        return lerp(a, b, t);
    }

};


#endif