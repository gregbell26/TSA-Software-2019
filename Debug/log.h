//
// Created by Gregory Bell on 9/18/19.
//

#ifndef TSA_SOFTWARE_2019_LOG_H
#define TSA_SOFTWARE_2019_LOG_H

#include <iostream>
#include <fstream>
#include <string>

#define COLOR_ERROR
#define COLOR_INFO
#define COLOR_WARNING

class Logger {
public:

    enum ERROR_LEVEL{
        INFORMATION = 0, WARNING, ERROR, FATAL
    };

private :
    //std::ifstream fin;
    std::ofstream fout;

    bool usingFile;
    bool usingConsole;

    bool isFileOpen = false;

    int activeErrorLevel;

public :
    Logger ();

    Logger(ERROR_LEVEL errorLevel, bool usingFile, bool usingConsole);

    int initLogger();

    void Log();

private:
    void information(std::string caller, std::string message);

    void warn(std::string caller, std::string message);

    void error(std::string caller, std::string message);

    void fatal(std::string caller, std::string message);
};






#endif //TSA_SOFTWARE_2019_LOG_H
