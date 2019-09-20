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

void Logger::Log() {

}


//Private Functions

void Logger::information(std::string caller, std::string message) {

}

void Logger::warn(std::string caller, std::string message) {

}

void Logger::error(std::string caller, std::string message) {

}

void Logger::fatal(std::string caller, std::string message) {

}


//TST function
int main() {

    return 0;
}
