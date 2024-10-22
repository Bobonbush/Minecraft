#ifndef __PHYSICVARIABLE_H__
#define __PHYSICVARIABLE_H__




class PhysicConstant
{
    private:

        
        
        const float CONSTANTOFFSET = 30.f;
        const float GRAVITY = 9.8f * 1.5f;
        const float PLAYER_MASS = 0.1f;
        


        /*
        Fricton of each Blocks
        */

        


        static PhysicConstant* instance;
        PhysicConstant()  = default;
    public:

        const float DEFAULTFriction = 0.1f;

        static PhysicConstant* getInstance() {
            if (instance == nullptr) {
                instance = new PhysicConstant();
            }
            return instance;
        }
        ~PhysicConstant() {
            if(instance != nullptr)
                delete instance;
        }

        float getGravity() {
            return GRAVITY;
        }

        float getPlayerMass() {
            return PLAYER_MASS;
        }

        float getConstantOffset() {
            return CONSTANTOFFSET;
        }
        
};



#endif