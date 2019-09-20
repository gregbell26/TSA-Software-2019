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


}

void Logger::Log(Logger::ERROR_LEVEL errorLevel, std::string caller, std::string message) {
    if (!(errorLevel >= activeErrorLevel))
        return;
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
    std::cout << "[" << *caller << "] " << COLOR_INFO << *message << COLOR_RESET<< std::endl;
}

void Logger::warn(std::string *caller, std::string *message) {
    std::cout << "[" << *caller << "] " << COLOR_WARNING << *message << COLOR_RESET<< std::endl;

}

void Logger::error(std::string *caller, std::string *message) {
    std::cout << "[" << *caller << "] " << COLOR_ERROR << *message << COLOR_RESET<< std::endl;

}

void Logger::fatal(std::string *caller, std::string *message) {
    const std::string RUNTIME_ERROR = "[" + *caller + "] " + *message;
    std::cout << "[" << *caller << "] " << COLOR_ERROR << *message << COLOR_RESET<< std::endl;

    throw std::runtime_error(RUNTIME_ERROR);
}


//TST function
int main() {
    auto *logger = new Logger(Logger::INFORMATION, false, true);

    logger->Log(logger->WARNING, "Main", "YEE!");
    logger->Log(logger->INFORMATION, "Main", "YEE!");
    logger->Log(logger->ERROR, "Main", "YEE!");
    logger->Log(logger->INFORMATION, "Main", "YEE!");





    return 0;
}
