#ifndef __PHYSICVARIABLE_H__
#define __PHYSICVARIABLE_H__




class PhysicConstant
{
    private:

        
        
        const float CONSTANTOFFSET = 64.f;
        const float GRAVITY = 9.8f;
        const float PLAYER_MASS = 50.0f;


        static PhysicConstant* instance;
        PhysicConstant()  = default;
    public:

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