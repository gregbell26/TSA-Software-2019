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

        std::map<std::string, int*> iamap;
        std::map<std::string, float*> famap;
        std::map<std::string, std::string*> samap;
        std::map<std::string, jsonMaps*> jamap;
    };

    void interpretArray(std::string toArr, std::string key, jsonMaps* where);
    jsonMaps interpretJson(std::string stringJson);

    void interpretArray(std::string toArr, std::string key, jsonMaps* where) {
        try {
            std::cout << toArr << "\n";
            if (!toArr[0])
                return;
            int elem = 0;
            int size = 0;
            int i = 0;
            bool notInQuotes = 1;
            unsigned loc = 0;
            unsigned next = -1;

            int *iaval;
            float *faval;
            std::string *saval;
            jsonMaps *javal;

            do {
                next = toArr.find_first_of("{}\",", next + 1);
                if (next == -1)
                    break;

                if (toArr[next] == '{' && notInQuotes)
                    i++;
                else if (toArr[next] == '}' && notInQuotes)
                    i--;
                else if (toArr[next] == '\"')
                    notInQuotes = !notInQuotes;
                else if (i == 0 && notInQuotes)
                    size++;

            } while (true);
            size++;
            std::cout << "size:" << size << "\n";

            next = toArr.find_first_of(',', loc);


            if (toArr[loc] == '{') {
                javal = new jsonMaps[size];
                elem = 0;
                while (elem < size && loc != -1) {
                    if (loc != 0)
                        loc++;
                    i = 1;
                    next = loc;
                    notInQuotes = 1;
                    do {

                        next = toArr.find_first_of("{}\"", next + 1);

                        if (toArr[next] == '{' && notInQuotes)
                            i++;
                        else if (toArr[next] == '}' && notInQuotes)
                            i--;
                        else if (toArr[next] == '\"')
                            notInQuotes = !notInQuotes;

                    } while (i != 0);
                    std::cout << loc << " " << next << "\n";
                    std::cout << toArr.substr(loc, next - loc + 1) << "\n";
                    std::cout << key << " -j- " << "{" << "\n";
                    javal[elem] = interpretJson(toArr.substr(loc, next - loc + 1));
                    std::cout << "}" << "\n";

                    elem++;
                    loc = toArr.find_first_of(",", next);
                }
                next++;
                where->jamap.insert_or_assign(key, javal);
            } else if (toArr[loc] == '\"') {
                saval = new std::string[size];
                elem = 0;
                while (elem < size) {
                    std::cout << loc << "\n";
                    saval[elem] = toArr.substr(loc + 1, next - loc - 2);
                    std::cout << key << " -s- " << saval[elem] << "\n";
                    loc = next + 1;
                    next = toArr.find_first_of(",", next + 1);
                    if (next == -1)
                        next = toArr.length();
                    elem++;
                }
                where->samap.insert_or_assign(key, saval);

            } else if (toArr.find_first_of('.', loc) != -1 && toArr.find_first_of('.', loc) < next) {
                faval = new float[size];
                elem = 0;
                while (elem < size) {
                    std::cout << loc << "\n";
                    faval[elem] = std::stof(toArr.substr(loc, next - loc));
                    std::cout << key << " -d- " << faval[elem] << "\n";
                    loc = next + 1;
                    next = toArr.find_first_of(",", next + 1);
                    elem++;
                }
                where->famap.insert_or_assign(key, faval);
            } else {
                iaval = new int[size];
                elem = 0;
                while (elem < size) {
                    std::cout << loc << "\n";
                    iaval[elem] = std::stoi(toArr.substr(loc, next - loc));
                    std::cout << key << " -i- " << iaval[elem] << "\n";
                    loc = next + 1;
                    next = toArr.find_first_of(",", loc);
                    elem++;
                }
                where->iamap.insert_or_assign(key, iaval);
            }
        }catch(const std::out_of_range){
            std::cerr << "Invalid Json" << std::endl;
            return;
        }catch(...){
            std::cerr << "Unknown Error" << std::endl;
            return;
        }
    }

        jsonMaps interpretJson(std::string stringJson) {
            try {

//        std::cout << stringJson << "\n";
            jsonMaps maps;
            std::string tempJson;
            tempJson.assign(stringJson);
            size_t loc = -1;
            size_t mid = 0;
            size_t end = 0;
            std::string key;
            bool notInQuotes = 1;
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

            std::cout << tempJson << "\n";

            do {
                loc++;
                mid = tempJson.find_first_of(':', loc);
                end = tempJson.find_first_of(',', mid);
                if (mid == -1)
                    break;
                if (end == -1)
                    end = tempJson.length();

                std::cout << mid << " " << end << "\n";
                //std::cout << tempJson[mid] << " " << tempJson[end] << "\n";
                std::cout << tempJson.find_first_of(",", mid, end - mid) << "\n";
                key = tempJson.substr(loc, mid - loc - 1);
                if (key[0] == '\"')
                    key.erase(0, 1);
                if (key[key.length() - 1] == '\"')
                    key.erase(key.length() - 1, 1);

                if (tempJson[mid + 1] == '{') {
                    i = 0;
                    end = mid;
                    notInQuotes = 1;
                    do {
                        end = tempJson.find_first_of("{}\"", end + 1);

                        if (tempJson[end] == '{' && notInQuotes)
                            i++;
                        else if (tempJson[end] == '}' && notInQuotes)
                            i--;
                        else if (tempJson[end] == '\"')
                            notInQuotes = !notInQuotes;

                    } while (i != 0);
                    std::cout << key << " -j- " << "{" << "\n";
                    jval = interpretJson(stringJson.substr(mid + 2, end - mid));
                    end++;
                    std::cout << "}" << "\n";
                    maps.jmap.insert_or_assign(key, jval);
                } else if (tempJson[mid + 1] == '[') {
                    i = 0;
                    end = mid;
                    do {
                        end = tempJson.find_first_of("[]", end + 1);
                        if (tempJson[end] == '[')
                            i++;
                        else
                            i--;
                    } while (i != 0);
                    std::cout << key << " -a- " << "[" << "\n";
                    interpretArray(tempJson.substr(mid + 2, end - mid - 2), key, &maps);
                    end++;
                    std::cout << "]" << "\n";
                } else if (tempJson[mid + 1] == '\"') {
                    sval = tempJson.substr(mid + 2, end - mid - 3);
                    std::cout << key << " -s- " << sval << "\n";
                    maps.smap.insert_or_assign(key, sval);
                } else if (tempJson.find_first_of('.', mid) != -1 && tempJson.find_first_of('.', mid) < end) {
                    fval = std::stof(tempJson.substr(mid + 1, end - mid - 1));
                    std::cout << key << " -d- " << fval << "\n";
                    maps.fmap.insert_or_assign(key, fval);
                } else {
                    ival = std::stoi(tempJson.substr(mid + 1, end - mid - 1));
                    std::cout << key << " -i- " << ival << "\n";
                    maps.imap.insert_or_assign(key, ival);
                }
                loc = end;
                std::cout << loc << "\n\n";
            } while (loc != -1);

            return maps;
        }catch(const std::out_of_range) {
            std::cerr << "Invalid Json" << std::endl;
            jsonMaps errorJson;
            return errorJson;
        }catch(...){
            std::cerr << "Unknown Error" << std::endl;
            jsonMaps errorJson;
            return errorJson;
        }
    }
}




#endif //ACRYLIC_FILESYSYTEM_HPP