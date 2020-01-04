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

struct jsonMaps{
    std::map<std::string, int> imap;
    std::map<std::string, double> dmap;
    std::map<std::string, std::string> smap;
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

jsonMaps interpretJson(std::string stringJson){
    jsonMaps maps;
    std::string json;
    json.assign(stringJson);
    unsigned loc = 0;
    unsigned mid = 0;
    unsigned end = 0;
    std::string key;
    int ival;
    double dval;
    std::string sval;
    int i = 0;
    while(i < stringJson.length()){
        if(stringJson[i] == ' ' || stringJson[i] == '\n')
            json.erase(i);
        else
            i++;
    }

    do{
        mid = json.find_first_of(":",loc);
        end = json.find_first_of(",",loc);
        key = json.substr(loc, mid-1);
        if(key[0] == '\"')
            key.erase(0);
        if(key[key.length()-1] == '\"')
            key.erase(key.length()-1);
        if(json[mid] == '\"') {
            sval = json.substr(mid + 1, end - 1);
            maps.smap.insert_or_assign(key,sval);
        }
        else if(json.find_first_of(".", mid, end) != -1) {
            dval = std::stod(json.substr(mid, end));
            maps.dmap.insert_or_assign(key, dval);
        }
        else {
            ival = std::stoi(json.substr(mid, end));
            maps.imap.insert_or_assign(key,ival);
        }
        loc = json.find_first_of(",",loc);
    }while(loc != -1);

    return maps;
}


void interpretString(std::string variable){

}


//void stringToJson(){
//
//}

#endif //ACRYLIC_FILESYSYTEM_HPP