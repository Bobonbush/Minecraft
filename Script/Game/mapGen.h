#include "Resource/TextureLoad.h"
#include "Resource/ShaderLoad.h"
#include "Blocks.h"
#define DB_PERLIN_IMPL
#include "Resource/db_perlin.hpp"
#include "Player.h"
#include "Algorithm.h"


class Gradient {
    public:

        glm::vec3 startPoints;
        glm::vec3 endPoints;
        ~Gradient() {
            //delete[] gradients;
        }
        Gradient() = default;

        void setGradient() {
            startPoints = glm::vec3(0.f, 0.f, 0.f);
            endPoints = glm::vec3(0.f, 112.f, 0.f);
        }

        float getGradient(float x, float y , float z) {
            glm::vec3 segmentVector = endPoints - startPoints;
            glm::vec3 pointVector = glm::vec3(x, y, z) - startPoints;
            if(glm::dot(segmentVector, segmentVector) == 0) {
                return 0;
            }
            float projection = glm::dot(pointVector, segmentVector) / glm::dot(segmentVector, segmentVector);
            
            return projection;

        }
};

// Shape Fractal
class FBM {
    private:

    int octaves = 8;
    float lacunarity = 2.0f;
    float gain = 0.5f;
    float offset = 0.2f;
    float scale = 0.5f;
    float H = 0.5f;
    float frequency = 1.0f;
    
    public:

    FBM(int octaves, float lacunarity, float gain, float offset, float scale, float H, float frequency, float amplitude) : octaves(octaves), lacunarity(lacunarity), gain(gain), offset(offset), scale(scale), H(H), frequency(frequency) {}
    FBM() = default;
    float getValue (float x, float y , float z) {
        float amplitude = 1.0f;
        float total = 0.0f;
        float maxValue = 0.0f;
        float persistence = 0.5f;

        for(int i = 0 ; i < octaves ; i++) {
            total += db::perlin(x * frequency, y * frequency, z * frequency) * amplitude;
            maxValue += amplitude;
            amplitude *= gain;
            frequency *= lacunarity;
        }

        float value = (total / maxValue) + offset;
        
        return (value + 1 ) /2 ;
    }
};

class Scaleoffset {
    float scale = 0.25f;
    float offset = 0.75f;
    FBM shapeFractal;

    public:
        Scaleoffset(float scale, float offset) : scale(scale), offset(offset) {}
        Scaleoffset() = default;

        float getValue(float x, float y, float z) {

            //std::cout << shapeFractal.getValue(x, y, z) << std::endl;
            return shapeFractal.getValue(x, y, z) * scale + offset;
            
        }
};



class GroundSelector {
    float low = 0.f;
    float high = 0.9f;
    float threshold = 0.5f;
    Scaleoffset scaleoffset;
    Gradient gradient;
    public:

    GroundSelector(float low, float high, float threshold, Scaleoffset scaleoffset, Gradient gradient) : low(low), high(high), threshold(threshold), scaleoffset(scaleoffset), gradient(gradient) {}
    GroundSelector() {
        gradient.setGradient();
    }
    float getValue(float x, float y, float z) {
        float value = scaleoffset.getValue(x, y, z);
        float gradientValue = gradient.getGradient(x, y, z);
        return gradientValue * value;
    }

    bool isGround(float x, float y, float z) {
        return getValue(x, y, z) > threshold;
    }
       
};
