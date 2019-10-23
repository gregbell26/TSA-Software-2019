#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;


std::string gameDataPath;


nlohmann::json* readJSONs(){
    std::fstream jsonStream;
    nlohmann::json levels[5];
    int i = 0;
    for(const auto& file : fs::directory_iterator(gameDataPath)){
        jsonStream.open(gameDataPath + file.path().string());
        levels[i] << (jsonStream >> *(new nlohmann::json));//note: >> operator is overloaded
        jsonStream.close();
        i++;
    }
    return levels;
}
