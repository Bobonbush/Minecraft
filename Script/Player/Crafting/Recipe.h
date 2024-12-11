#ifndef RECIPE_H
#define RECIPE_H
#include "Utils/File.h"
#include "Utils/Singleton.h"

class Recipe {

    public :
    enum class Type {
        CRAFTING,
        MELTING
            //BREWING
    };
    private:
        
        
       
        std::vector<std::pair<int ,int >> ingredients;
        std::string result;
        std::string RecipeFormula;
        int number = 0;
        Type type;
        
    public:
        
        Recipe(const Type & type, const std::string & name);
        Recipe() = default;
        ~Recipe() = default;
};


class CraftingRecipeDataBase : Singleton {
    private:

        std::vector<Recipe> recipes;
        Recipe::Type type;

        CraftingRecipeDataBase();

        static CraftingRecipeDataBase * instance;
    public:

        static CraftingRecipeDataBase * GetInstance() {
            if(instance == nullptr) {
                instance = new CraftingRecipeDataBase();
            }
            return instance;
        }
        ~CraftingRecipeDataBase() {
            delete instance;
        }




};

#endif // RECIPE_H