#ifndef RECIPE_H
#define RECIPE_H
#include "Utils/File.h"
#include "Utils/Singleton.h"
#include "Block/Block.h"
#include "Item/ItemDataBase.h"
#include "Algorithm.h"

class Recipe {

    public :
    enum class Type {
        CRAFTING,
        MELTING
            //BREWING
    };
    private:
        
        
       
        std::vector<std::string> ingredients;
        std::string result;
        std::string RecipeFormula;
        int number = 0;
        Type type;

        int matrix[3][3];
        
        void Convert();

        
    public:
        
        Recipe(const Type & type, const std::string & name);
        Recipe() = default;
        ~Recipe() = default;
        
        bool isMatch(const std::vector<std::vector<int>> & matrix);
        const std::string & getResult() const;

        const int getNumber() const {
            return number;
        }

        void Debug() {
            std::cout << "Recipe : " << result << std::endl;
            std::cout << "Ingredients : ";
            for(auto & ingredient : ingredients) {
                std::cout << ingredient << " ";
            }
            std::cout << std::endl;
            std::cout << "Formula : " << RecipeFormula << std::endl;
            std::cout << "Number : " << number << std::endl;
            std::cout << "Type : " << (int) type << std::endl;
        }

        
};


class CraftingRecipeDataBase : Singleton {
    private:

        std::vector<Recipe> recipes;
        Recipe::Type type;
        int number = 1;

        CraftingRecipeDataBase();

        static CraftingRecipeDataBase * instance;
    public:

        static CraftingRecipeDataBase * GetInstance() {
            if(instance == nullptr) {
                instance = new CraftingRecipeDataBase();
            }
            return instance;
        }
        ~CraftingRecipeDataBase();

        std::string isMatch(const std::vector<std::vector<int>> & matrix);

        const int getInstantNumber() const {
            return number;
        }




};

#endif // RECIPE_H