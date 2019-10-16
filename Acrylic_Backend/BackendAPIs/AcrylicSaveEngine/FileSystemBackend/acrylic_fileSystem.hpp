#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;


std::string gameDataPath;


std::vector<nlohmann::json*> readJSONs(){
    std::fstream jsonStream;
    std::vector<nlohmann::json*> levels;//just pointers
    for(const auto& file : fs::directory_iterator(gameDataPath)){
        jsonStream.open(gameDataPath + file.path().string());
        levels.push_back(&(jsonStream >> new nlohmann::json));//note: operator is overloaded, IDE just doesn't realize it
        jsonStream.close();
    }
    return levels;
}
