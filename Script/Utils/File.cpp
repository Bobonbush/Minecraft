#include "File.h"

File * File::instance = nullptr;

std::string File::ReadFile(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
        return "None";
    }
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    return stream.str();
}

void File::WriteFile(const std::string &path, const std::string &content) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
        return ;
    }
    file << content;
    file.close();
}

void File::SetJson(const std::string &path) {
    json j;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
        return ;
    }
    jsonData = j;
    file >> jsonData;
    file.close();
}

void File::SetNextJson(const std::string &Name) {
    jsonStack.push(jsonData);
    jsonData = jsonData[Name];
}

void File::PrintCurrentJson() {
    std::cout << jsonData.dump(4) << std::endl;
}

void File::PopJson() {
    jsonData = jsonStack.top();
    jsonStack.pop();
}

int File::GetJsonInt(const std::string &key) {
    return jsonData[key].get<int>();
}

float File::GetJsonFloat(const std::string &key) {
    return jsonData[key].get<float>();
}

std::string File::GetJsonString(const std::string &key) {
    return jsonData[key].get<std::string>();
}

bool File::GetJsonBool(const std::string &key) {
    return jsonData[key].get<bool>();
}

std::vector<std::string> File::GetJsonArray( const std::string &key) {
    std::vector<std::string> result;
    for (auto &element : jsonData[key]) {
        result.push_back(element.get<std::string>());
    }
    return result;
}