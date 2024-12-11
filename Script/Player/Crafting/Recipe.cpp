#include "Recipe.h"


Recipe::Recipe(const Type &type, const std::string & name) {
    this -> type = type;
    File * file = File::GetInstance();
    file -> SetJson("Assets/Crafting/crafting.json");
    RecipeFormula = name;
    file -> SetNextJson(name);
    if(type == Type::CRAFTING) {
        
        result = file -> GetJsonString("Result");
        number = file -> GetJsonInt("Number");
        RecipeFormula = file -> GetJsonString("Recipe"); 
        file -> SetNextJson("Ingredients");
    }
}