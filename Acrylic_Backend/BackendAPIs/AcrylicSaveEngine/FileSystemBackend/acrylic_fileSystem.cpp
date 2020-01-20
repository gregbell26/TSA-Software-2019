#include "acrylic_fileSystem.hpp"

namespace A2D::Filesystem::Loaders {
    fs::path gameDataPath("./GAME_DATA");
}

std::string A2D::Filesystem::Loaders::readFile(const std::string& fileName) {
    std::fstream jsonStream;// 1 stream for all different files
    std::string tempString;// temporary variable for transfer
    std::string fullFile;
    if (!fs::exists(gameDataPath)) {
        logError("File path \'" + gameDataPath.string() + "\' does not exist")
//        std::cerr << "File path does not exist\n";
        return std::string();
    }
    for (const auto &file : fs::directory_iterator(gameDataPath)) {
        if (file.path().filename().string() == fileName) {//looking for id
            jsonStream.open(file.path());
            while (jsonStream >> tempString) {
                fullFile.append(tempString);// hopefully this works
            }
            jsonStream.close();
            return fullFile;
        }
    }
//    std::cerr << "File not found\n";
    logError("File \'" + fileName + "\' was not found")
    return std::string();
}

void A2D::Filesystem::Loaders::setGameDataPath(const fs::path &newGameDataPath) {
    gameDataPath = newGameDataPath;
}


void A2D::Filesystem::Loaders::JSON::interpretArray(std::string toArr, const std::string& key, jsonMaps* where) {
    try {
        logInformation("Loading array: " + toArr)
//            std::cout << toArr << "\n";
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
//            std::cout << "size:" << size << "\n";
        logInformation("JSON Size: " + std::to_string(size))
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
//                    std::cout << loc << " " << next << "\n";
                logInformation("JSON starts at " + std::to_string(loc) + " and goes to " + std::to_string(next))
//                    std::cout << toArr.substr(loc, next - loc + 1) << "\n";
                logInformation("Json to be interpreted: " + toArr.substr(loc, next - loc + 1))
//                    std::cout << key << " -j- " << "{" << "\n";
                logInformation("Loading Json: " + key + " at " + std::to_string(elem))
                javal[elem] = interpretJson(toArr.substr(loc, next - loc + 1));
//                    std::cout << "}" << "\n";

                elem++;
                loc = toArr.find_first_of(',', next);
            }
            next++;
            where->jamap.insert_or_assign(key, javal);
        } else if (toArr[loc] == '\"') {
            saval = new std::string[size];
            elem = 0;
            while (elem < size) {
//                    std::cout << loc << "\n";

                saval[elem] = toArr.substr(loc + 1, next - loc - 2);
//                    std::cout << key << " -s- " << saval[elem] << "\n";
                logInformation("Loading string: " + saval[elem] + " at " + std::to_string(elem))
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
//                    std::cout << loc << "\n";
                faval[elem] = std::stof(toArr.substr(loc, next - loc));
//                    std::cout << key << " -d- " << faval[elem] << "\n";
                logInformation("Loading float: " + std::to_string(faval[elem]) + " at " + std::to_string(elem))
                loc = next + 1;
                next = toArr.find_first_of(',', next + 1);
                elem++;
            }
            where->famap.insert_or_assign(key, faval);
        } else {
            iaval = new int[size];
            elem = 0;
            while (elem < size) {
//                    std::cout << loc << "\n";
                iaval[elem] = std::stoi(toArr.substr(loc, next - loc));
//                    std::cout << key << " -i- " << iaval[elem] << "\n";
                logInformation("Loading Int: " + std::to_string(iaval[elem]) + " at " + std::to_string(elem))
                loc = next + 1;
                next = toArr.find_first_of(',', loc);
                elem++;
            }
            where->iamap.insert_or_assign(key, iaval);
        }
    }catch(const std::out_of_range& err){
        logError("Invalid Json")
//            std::cerr << "Invalid Json" << std::endl;
        return;
    }catch(const std::invalid_argument& err) {
        logError("Could not determine data type")
//            std::cerr << "Could not determine data type" << std::endl;
        return;
    }catch(...){
        logError("Unknown Error")
//            std::cerr << "Unknown Error" << std::endl;
        return;
    }
}

A2D::Filesystem::Loaders::JSON::jsonMaps A2D::Filesystem::Loaders::JSON::interpretJson(const std::string& stringJson) {
    try {
        if(stringJson.empty()) {
            logError("Input is empty")
//                std::cerr << "Input is empty" << std::endl;
            jsonMaps errorJson;
            return errorJson;
        }
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
        logInformation("JSON to interpret: " + tempJson)
        //            std::cout << tempJson << "\n";

        do {
            loc++;
            mid = tempJson.find_first_of(':', loc);
            end = tempJson.find_first_of(',', mid);
            if (mid == -1)
                break;
            if (end == -1)
                end = tempJson.length();

            //                std::cout << mid << " " << end << "\n";
            logInformation("Starting at " + std::to_string(mid) + " going to " + std::to_string(end))
            //                std::cout << tempJson.find_first_of(",", mid, end - mid) << "\n";
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
                logInformation("Loading JSON: " + key)
                //                    std::cout << key << " -j- " << "{" << "\n";
                jval = interpretJson(stringJson.substr(mid + 2, end - mid));
                end++;
                //                    std::cout << "}" << "\n";
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
                //                    std::cout << key << " -a- " << "[" << "\n";
                interpretArray(tempJson.substr(mid + 2, end - mid - 2), key, &maps);
                end++;
                //                    std::cout << "]" << "\n";
            } else if (tempJson[mid + 1] == '\"') {
                sval = tempJson.substr(mid + 2, end - mid - 3);
                logInformation("Loading String: " + sval + " at " + key)
                //                    std::cout << key << " -s- " << sval << "\n";
                maps.smap.insert_or_assign(key, sval);
            } else if (tempJson.find_first_of('.', mid) != -1 && tempJson.find_first_of('.', mid) < end) {
                fval = std::stof(tempJson.substr(mid + 1, end - mid - 1));
                logInformation("Loading Float: " + std::to_string(fval) + " at " + key)
                //                    std::cout << key << " -d- " << fval << "\n";
                maps.fmap.insert_or_assign(key, fval);
            } else {
                ival = std::stoi(tempJson.substr(mid + 1, end - mid - 1));
                logInformation("Loading Int: " + std::to_string(ival) + " at " + key)
                //                    std::cout << key << " -i- " << ival << "\n";
                maps.imap.insert_or_assign(key, ival);
            }
            loc = end;
            //                std::cout << loc << "\n\n";
        } while (loc != -1);

        return maps;

    } catch(const std::out_of_range& err) {
        logError("Invalid Json")
//            std::cerr << "Invalid Json" << std::endl;
        jsonMaps errorJson = {};

        return errorJson;
    } catch(const std::invalid_argument& err) {
        logError("Could not determine data type")
//            std::cerr << "Could not determine data type" << std::endl;
        jsonMaps errorJson = {};

        return errorJson;
    } catch(...){
        logError("Unknown Error")
//            std::cerr << "Unknown Error" << std::endl;
        jsonMaps errorJson = {};

        return errorJson;
    }
}

