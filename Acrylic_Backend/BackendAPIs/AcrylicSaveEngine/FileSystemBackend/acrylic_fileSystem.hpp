#ifndef ACRYLIC_FILESYSTEM_HPP
#define ACRYLIC_FILESYSTEM_HPP

#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>
#include <map>
namespace fs = std::filesystem;

union primitiveType{
    char ch;
    short s;
    int i;
    long l;
    unsigned char u_ch;
    unsigned short u_s;
    unsigned int u_i;
    unsigned long u_l;
    float f;
    double d;
    bool b;
};

fs::path gameDataPath("./GAME_DATA");


std::string readFile(std::string fileName){
    std::fstream jsonStream;// 1 stream for all different files
    std::string tempString;// temporary variable for transfer
    std::string fullFile;
    if(!fs::exists(gameDataPath)){
        std::cerr << "File path does not exist\n";
        return "";
    }
    for(const auto& file : fs::directory_iterator(gameDataPath)) {
        if (!file.path().filename().string().compare(fileName)) {//looking for id
            jsonStream.open(file.path());
            while(jsonStream >> tempString) {
                fullFile.append(tempString);// hopefully this works
            }
            jsonStream.close();
            return fullFile;
        }
    }
    std::cerr << "File not found\n";
    return "";
}

std::map<std::string, primitiveType> interpretJson(std::string stringJson){
    while(stringJson.find(":") != -1)
        ;
    while(stringJson.find("\"") != -1)
        ;
    while(stringJson.find(",") != -1)
        ;

    return std::map<std::string, primitiveType>();//TEMP FIX BY GREGORY
}



//void stringToJson(){
//
//}

#endif //ACRYLIC_FILESYSYTEM_HPP