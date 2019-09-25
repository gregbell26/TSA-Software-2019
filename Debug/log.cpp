//
// Created by Gregory Bell on 9/18/19.
//

#include "log.h"
//Constructors
Logger::Logger() {

    usingFile = false;
    usingConsole = true;
    activeErrorLevel = INFORMATION;

}

Logger::Logger(Logger::ERROR_LEVEL errorLevel, bool usingFile, bool usingConsole) {
    this->usingFile = usingFile;
    this->usingConsole = usingConsole;
    this->activeErrorLevel = errorLevel;
}


//Public functions
int Logger::initLogger() {
    if(usingFile){
        fout.open("acrylic.log", std::fstream::out | std::fstream::app);//Opens file for output and will add to the end of the file
        isFileOpen = fout.is_open();
        if(!isFileOpen) {
            log(ERROR, "Logger", "Failed to open log file");
            return -1;
        }
        fout << "<<<<<Log Started>>>>>\n";
        fout.flush();

    }
    return 0;
}

void Logger::log(Logger::ERROR_LEVEL errorLevel, std::string caller, std::string message) {
    if(!usingConsole && !usingFile)//If log is disabled then quit to prevent resource allocation
        return;

    if (!(errorLevel >= activeErrorLevel))
        return;

    //Splitters
    if (errorLevel == INFORMATION)
        information(&caller, &message);
    else if (errorLevel == WARNING)
        warn(&caller, &message);
    else if (errorLevel == ERROR)
        error(&caller, &message);
    else if (errorLevel == FATAL)
        fatal(&caller, &message);
}

//Private Functions

void Logger::information(std::string *caller, std::string *message) {
    if(usingFile){
        fout << "INFORMATION: [" << *caller << "] " << *message <<"\n";
        fout.flush();
    }
    if(usingConsole)
        std::cout << "[" << *caller << "] " << COLOR_INFO << *message << COLOR_RESET<< std::endl;
}

void Logger::warn(std::string *caller, std::string *message) {
    if(usingFile){
        fout << "WARNING: [" << *caller << "] " << *message <<"\n";
        fout.flush();
    }
    if(usingConsole)
        std::cout << "[" << *caller << "] " << COLOR_WARNING << *message << COLOR_RESET<< std::endl;

}

void Logger::error(std::string *caller, std::string *message) {
    if(usingFile){
        fout << "ERROR: [" << *caller << "] " << *message <<"\n";
        fout.flush();
    }
    if(usingConsole)
        std::cout << "[" << *caller << "] " << COLOR_ERROR << *message << COLOR_RESET<< std::endl;

}

void Logger::fatal(std::string *caller, std::string *message) {
    const std::string RUNTIME_ERROR = "[" + *caller + "] " + *message;
    std::cout << "[" << *caller << "] " << COLOR_ERROR << *message << COLOR_RESET<< std::endl;

    throw std::runtime_error(RUNTIME_ERROR);
}

//Deconstruct-er
Logger::~Logger() {
    if(usingFile) {
        fout << "<<<<<Log Ended>>>>>\n";
        fout.flush();
        fout.close();
    }
}


//TST function
int main() {
    auto *logger = new Logger(Logger::INFORMATION, true, true);
    logger->initLogger();
    logger->log(logger->WARNING, "Main", "Warning");
    logger->log(logger->INFORMATION, "Main", "Information");
    logger->log(logger->ERROR, "Main", "Error");
    logger->log(logger->INFORMATION, "Main", "Information");
    logger->log(logger->FATAL, "Main", "Fatal");

    delete logger;


    logger = nullptr;

    std::cin.get();
    return 0;
}
