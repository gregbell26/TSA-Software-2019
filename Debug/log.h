//
// Created by Gregory Bell on 9/18/19.
//

#ifndef TSA_SOFTWARE_2019_LOG_H
#define TSA_SOFTWARE_2019_LOG_H

#include <iostream>
#include <fstream>
#include <string>

//#define COLOR_ERROR
//#define COLOR_INFO
//#define COLOR_WARNING
//#define COLOR_RESET

#if defined(MACOS) || defined(LINUX)
#define COLOR_INFO "\033[34m" //
#define COLOR_WARNING "\033[33m"
#define COLOR_ERROR "\033[31;1m"
#define COLOR_RESET "\033[0m"

#elif defined(WINDOWS)
#define COLOR_INFO 1325ED
#define COLOR_WARNING EDE613
#define COLOR_ERROR FF0000
#define COLOR_RESET FFFFFF

#endif


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

    void log(ERROR_LEVEL errorLevel, std::string caller, std::string message);

    ~Logger();

private:
    void information(std::string *caller, std::string *message);

    void warn(std::string *caller, std::string *message);

    void error(std::string *caller, std::string *message);

    static void fatal(std::string *caller, std::string *message);
};






#endif //TSA_SOFTWARE_2019_LOG_H
