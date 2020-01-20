#ifndef ACRYLIC_FILESYSTEM_HPP
#define ACRYLIC_FILESYSTEM_HPP

#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <map>
#include <ths/log.hpp>


namespace fs = std::filesystem;

namespace A2D::Filesystem::Loaders{

    std::string readFile(const std::string& fileName);

    void setGameDataPath(const fs::path& newGameDataPath);

}

namespace A2D::Filesystem::Loaders::JSON {


    struct jsonMaps {
        std::map<std::string, int> imap;
        std::map<std::string, float> fmap;
        std::map<std::string, std::string> smap;
        std::map<std::string, jsonMaps> jmap;

        std::map<std::string, int*> iamap;
        std::map<std::string, float*> famap;
        std::map<std::string, std::string*> samap;
        std::map<std::string, jsonMaps*> jamap;
    };

    void interpretArray(std::string toArr, const std::string& key, jsonMaps* where);
    jsonMaps interpretJson(const std::string& stringJson);
}




#endif //ACRYLIC_FILESYSYTEM_HPP