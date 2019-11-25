#ifndef ACRYLIC_FILESYSTEM_HPP
#define ACRYLIC_FILESYSTEM_HPP

#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;


std::string gameDataPath = "./GAME_DATA";


nlohmann::json readJSON(char id/*the final character, will probably change later*/){
    std::fstream jsonStream;// 1 stream for all different files
    nlohmann::json level;// class, will be returned
    std::string stringJson;// temporary variable for transfer
    for(const auto& file : fs::directory_iterator(gameDataPath)) {
        if (file.path().string()[file.path().string().length()-1] == id) {//looking for id
            jsonStream.open(gameDataPath + file.path().string());
            jsonStream >> stringJson;// hopefully this works
            level = nlohmann::json::parse(stringJson);
            jsonStream.close();
            break;// Note will only get the first of dupes
        }
    }
    return level;
}

#endif //ACRYLIC_FILESYSYTEM_HPP