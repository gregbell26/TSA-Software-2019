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

namespace A2D::Filesystem::Loaders{

    fs::path gameDataPath("./GAME_DATA");

    std::string readFile(std::string fileName) {
        std::fstream jsonStream;// 1 stream for all different files
        std::string tempString;// temporary variable for transfer
        std::string fullFile;
        if (!fs::exists(gameDataPath)) {
            std::cerr << "File path does not exist\n";
            return "";
        }
        for (const auto &file : fs::directory_iterator(gameDataPath)) {
            if (!file.path().filename().string().compare(fileName)) {//looking for id
                jsonStream.open(file.path());
                while (jsonStream >> tempString) {
                    fullFile.append(tempString);// hopefully this works
                }
                jsonStream.close();
                return fullFile;
            }
        }
        std::cerr << "File not found\n";
        return "";
    }
}

namespace A2D::Filesystem::Loaders::Json {


    struct jsonMaps {
        std::map<std::string, int> imap;
        std::map<std::string, float> fmap;
        std::map<std::string, std::string> smap;
        std::map<std::string, jsonMaps> jmap;
    };

    jsonMaps interpretJson(std::string stringJson) {
        jsonMaps maps;
        std::string tempJson;
        tempJson.assign(stringJson);
        size_t loc = -1;
        size_t mid = 0;
        size_t end = 0;
        std::string key;
        int ival;
        float fval;
        std::string sval;
        jsonMaps jval;
        int i = 0;

        while (i < tempJson.length()) {
            if (tempJson[i] == ' ' || tempJson[i] == '\n')
                tempJson.erase(i, 1);
            else
                i++;
        }

        if (tempJson[0] == '{')
            tempJson.erase(0, 1);
        if (tempJson[tempJson.length() - 1] == '}')
            tempJson.erase(tempJson.length() - 1, 1);

//        std::cout << tempJson << "\n";

        do {
            loc++;
            mid = tempJson.find_first_of(':', loc);
            end = tempJson.find_first_of(',', loc);
            if (mid == -1)
                break;
            if (end == -1)
                end = tempJson.length();

//            std::cout << mid << " " << end << "\n";
//            std::cout << tempJson.find_first_of(".", mid, end - mid ) << "\n";
            key = tempJson.substr(loc, mid - loc - 1);
            if (key[0] == '\"')
                key.erase(0, 1);
            if (key[key.length() - 1] == '\"')
                key.erase(key.length() - 1, 1);

            if (tempJson[mid + 1] == '{') {
                i = 0;
                end=mid;
                do {
                    end = tempJson.find_first_of("{}", end + 1);

                    if(tempJson[end] == '{' )
                        i++;
                    else
                        i--;
                }while(i!=0);
//                std::cout << key << " -j- " << "{" << "\n";
                jval = interpretJson(stringJson.substr(mid+2,end-mid));
                end++;
//                std::cout << "}" << "\n";
                maps.jmap.insert_or_assign(key, jval);
            }
            else if (tempJson[mid + 1] == '\"') {
                sval = tempJson.substr(mid + 2, end - mid - 3);
//                std::cout << key << " -s- " << sval << "\n";
                maps.smap.insert_or_assign(key, sval);
            } else if (tempJson.find_first_of('.', mid) != -1 && tempJson.find_first_of('.', mid) < end) {
                fval = std::stof(tempJson.substr(mid + 1, end - mid - 1));
//                std::cout << key << " -d- " << fval << "\n";
                maps.fmap.insert_or_assign(key, fval);
            } else {
                ival = std::stoi(tempJson.substr(mid + 1, end - mid - 1));
//                std::cout << key << " -i- " << ival << "\n";
                maps.imap.insert_or_assign(key, ival);
            }
            loc = tempJson.find_first_of(',', loc);
//            std::cout << loc << "\n\n";
        } while (loc != -1);

        return maps;
    }
}


#endif //ACRYLIC_FILESYSYTEM_HPP