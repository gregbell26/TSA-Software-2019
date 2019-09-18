//
// Created by Gregory Bell on 9/18/19.
//

#ifndef TSA_SOFTWARE_2019_LOG_H
#define TSA_SOFTWARE_2019_LOG_H

#include <iostream>
#include <fstream>
#include <string>
class Logger{
private :
    std::ifstream fin;
    std::ofstream fout;
    bool usingFile;
    bool usingConsole;
    enum ERROR_LEVEL{
        INFORMATION = 0, WARNING, ERROR, FATAL;
    };
    int activeErrorLevel = INFORMATION;
public :
    Logger ();
    Logger(ERROR_LEVEL errorLevel, bool usingFile, bool usingConsole);
    void Log();

};






#endif //TSA_SOFTWARE_2019_LOG_H
