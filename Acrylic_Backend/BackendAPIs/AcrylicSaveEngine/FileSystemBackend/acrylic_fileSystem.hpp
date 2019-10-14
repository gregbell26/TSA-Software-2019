#include <fstream>
#include <string>
#include <filesystem>
#include <list>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;


std::string gameDataPath;


std::string readJSONs(){
    std::fstream jsonStream;

    for(const auto& file : fs::directory_iterator(gameDataPath)){
        jsonStream.open(gameDataPath + file.path().string());

        jsonStream.close();
    }
    std::fstream stream;

}
