#include "Recipe.h"


Recipe::Recipe(const Type &type, const std::string & name) {
    this -> type = type;
    File * file = File::GetInstance();
    file -> SetJson("Assets/Crafting/crafting.json");

    
    if(type == Type::CRAFTING) {
        
        file -> SetNextJson("Craft");
        file -> SetNextJson(name);
        
        result = file -> GetJsonString("Result");
        number = file -> GetJsonInt("Number");
        RecipeFormula = file -> GetJsonString("Recipe"); 

        ingredients = file -> GetJsonArray("Ingredients");

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    Convert();

    
    
}

void Recipe::Convert() {

    ItemDataBase * itemDataBase = ItemDataBase::GetInstance();
    if(type == Type::CRAFTING) {
        std::vector<int> number ((int) ingredients.size() , 0);
        for(int i = 0; i < (int) ingredients.size(); i++) {
            number[i] = itemDataBase -> getItemID(ingredients[i]);
        }
    
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                matrix[i][j] = RecipeFormula[i * 3 + j] - '0';
                if(matrix[i][j] != 0) 
                    matrix[i][j] = number[matrix[i][j] -1];
                else {
                    matrix[i][j] = 0;
                }

            }
        }

        std::vector<std::vector<int>> temp(3, std::vector<int>(3, 0));
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                temp[i][j] = matrix[i][j];
            }
        }

        SPA::ShiftFullyToTopLeft(temp);

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                
                matrix[i][j] = temp[i][j];
            }
        
        }


        

        
    }
}

bool Recipe::isMatch(const std::vector<std::vector<int>> & matrix) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(this -> matrix[i][j] != matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

const std::string & Recipe::getResult() const {
    return result;
}


CraftingRecipeDataBase * CraftingRecipeDataBase::instance = nullptr;

CraftingRecipeDataBase::CraftingRecipeDataBase() {
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Planks"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Crafting Table"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Sticks"));

    

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Iron Sword"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Sword"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Sword"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Sword"));

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Iron Pickaxe"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Pickaxe"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Pickaxe"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Pickaxe"));

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Iron Axe"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Axe"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Axe"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Axe"));

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Iron Helmet"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Helmet"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Helmet"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Helmet"));

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Iron Chestplate"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Chestplate"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Chestplate"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Chestplate"));

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Iron Leggings"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Leggings"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Leggings"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Leggings"));

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Iron Boots"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Boots"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Boots"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Boots"));
    
    
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Coal Block"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper Block"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser Block"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue Block"));

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "TNT"));
    

    

    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Blue"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Laser"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Copper"));
    recipes.push_back(Recipe(Recipe::Type::CRAFTING, "Coal"));
    
}

CraftingRecipeDataBase::~CraftingRecipeDataBase() {
    delete instance;
}

std::string CraftingRecipeDataBase::isMatch(const std::vector<std::vector<int>> & matrix) {
    for(Recipe & recipe : recipes) {
        if(recipe.isMatch(matrix)) {
            number = recipe.getNumber();
            return recipe.getResult();
        }
    }
    return "null";
}