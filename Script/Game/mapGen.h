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
            Setting * settings = Setting::getInstance();
            int y = settings -> getChunkSize().y * 0.85f * settings -> getBlockNDCSize().y;
            startPoints = glm::vec3(0.f, 0.f, 0.f);
            endPoints = glm::vec3(0.f, y, 0.f);
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
    float frequency = 1.f;
    float amplitude = 1.f;
    
    public:

    FBM(int octaves, float lacunarity, float gain, float frequency, float amplitude) : octaves(octaves), lacunarity(lacunarity), gain(gain), frequency(frequency), amplitude(amplitude){}
    FBM() = default;
    float getValue (float x, float y , float z) const {
        float ampli = amplitude;

        float total = 0.0f;
        float maxValue = 0.0f;
        float persistence = 0.5f;
        float freq = frequency;
        Setting * settings = Setting::getInstance();

        for(int i = 0 ; i < octaves ; i++) {
            float offset = 1058.f * settings -> getChunkSize().x;
            float offset_y = (float) settings -> getChunkSize().y * 2.f ; 
            total += db::perlin(x /offset  * freq ,  z/offset * freq) * ampli;
            //std::cout << freq << ' ' << lacunarity << ' ' << gain << ' ' << ampli << '\n';
            //std::cout << x /offset * freq << ' ' << y/offset_y * freq << ' ' << z/offset * freq << '\n';
            //std::cout << "Noise : " << db::perlin(x /offset * freq , y/offset_y * freq, z/offset * freq)  << '\n';
            maxValue += ampli;
            ampli *= gain;
            freq *= lacunarity;
        }

        //std::cout << total << ' ' << maxValue << '\n';
        float value = (total / maxValue);
        value = total;
        value += 1.f;
        value /= 2.f;
        //std::cout << value <<'\n';

        value = pow(value, 1.75);
        return value  ;
    }
};

class Scaleoffset {
    float scale = 1.25f;
    float offset = 0.55f;
    FBM shapeFractal;

    public:
        Scaleoffset(float scale, float offset) : scale(scale), offset(offset) {
            shapeFractal = FBM(8, 2.0f, 0.5f, 0.00005f, 2.f);
        }
        Scaleoffset() {
            shapeFractal = FBM(4, 2.00f, 0.5f, 10.5, 1.f);
        }

        float getValue(float x, float y, float z) {

            //std::cout << shapeFractal.getValue(x, y, z) << std::endl;
            float ans = shapeFractal.getValue(x, y, z) * scale + offset * shapeFractal.getValue(x, y ,z );
            SPA::clamp(ans , 0.f, 1.f);
            return ans;
        }
};



class GroundSelector {
    float low = 0.f;
    float high = 1.f;
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
        float gradientValue =  gradient.getGradient(x, y, z);
        //std::cout << value  << ' ' << gradientValue << '\n';
        //float blended =  low + (high - low) * (gradientValue * (1 - gradientValue) * value);
        float offset = 0.8f;
        return glm::mix(value , gradientValue , 0.4f);
    }

    bool isGround(float x, float y, float z) {
        return getValue(x, y, z) < threshold;
    }
       
};
