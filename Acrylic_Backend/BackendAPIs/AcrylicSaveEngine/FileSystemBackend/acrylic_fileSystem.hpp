#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;


std::string gameDataPath;


nlohmann::json readJSON(char id){
    std::fstream jsonStream;
    nlohmann::json level;
    std::string stringJson;
    for(const auto& file : fs::directory_iterator(gameDataPath)) {
        if (file.path().string()[file.path().string().length()] == id) {
            jsonStream.open(gameDataPath + file.path().string());
            jsonStream >> stringJson;//note: >> operator is overloaded
            level = nlohmann::json::parse(stringJson);
            jsonStream.close();
        }
    }
    return level;
}
