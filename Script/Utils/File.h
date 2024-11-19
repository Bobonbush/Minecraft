#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <Singleton.h>
#include <nlohmann/json.hpp>
class File : public Singleton  {
    File() = default;
    static File * instance;
    using json = nlohmann::json;
    json jsonData;

    

    public : 
    static File * GetInstance() {
        if(instance == nullptr) {
            instance = new File();
        }
        return instance;
    }
    ~File() {
        delete instance;
    }
    std::string ReadFile(const std::string & path);
    void WriteFile(const std::string & path, const std::string & content);
    void SetJson(const std::string & path);

    int GetJsonInt(const std::string & key);
    float GetJsonFloat(const std::string & key);
    std::string GetJsonString(const std::string & key);
    bool GetJsonBool(const std::string & key);
};

#endif // FILE_H