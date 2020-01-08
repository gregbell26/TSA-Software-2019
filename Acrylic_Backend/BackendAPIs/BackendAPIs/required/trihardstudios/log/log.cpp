#include "../include/ths/log.hpp"

#if defined(Darwin) || defined(Linux)
#define A2D_COLOR_INFO "\033[34m" //
#define A2D_COLOR_WARNING "\033[33m"
#define A2D_COLOR_ERROR "\033[31;1m"
#define A2D_COLOR_RESET "\033[0m"

#elif defined(Windows)

#include <Windows.h>

//#undef ERROR
// blue
#define A2D_COLOR_INFO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY) // 1325ED
// yellow
#define A2D_COLOR_WARNING SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6) // EDE613
// red
#define A2D_COLOR_ERROR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12) // FF0000
// reset
#define A2D_COLOR_RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) // FFFFFF

#endif

static std::ofstream fout;
static const char *activeName;
static A2D::Log::SEVERITY activeSeverity;
static A2D::Log::MODE activeMode;
static bool init = false;

void A2D::Log::initLog(const char *name, Log::SEVERITY severity, Log::MODE mode)
{
    activeName = name;
    activeSeverity = severity;
    activeMode = mode;
    if(activeMode > MODE::A2D_CONSOLE_ONLY){
        std::filesystem::path logFilePath = name;
        logFilePath += "_log.log";
        fout.open(logFilePath);
        if(!fout.is_open()){
            activeMode = MODE::A2D_CONSOLE_ONLY;
            fout.close();
            log(SEVERITY::A2D_ERROR, "Failed to open log file. Using console for log.");
        }
    }
    log(SEVERITY::A2D_INFORMATION, "<<< LOG STARTED >>>");
    init = true;
}

void A2D::Log::log(Log::SEVERITY severity, const std::string &message) {
    if(activeSeverity > severity){
        return;
    }

    switch (severity){
        case SEVERITY::A2D_INFORMATION : info(message); break;
        case SEVERITY::A2D_WARNING     : warn(message); break;
        case SEVERITY::A2D_ERROR       : err (message); break;
    }
}

void A2D::Log::info(const std::string &message) {
    if(activeMode == MODE::A2D_CONSOLE_ONLY || activeMode == MODE::A2D_ALL) {
#if defined(Windows)
            std::cout << A2D_COLOR_INFO << "\b"
                << "[" << activeName << ": INFORMATION] " << message
                << std::endl;
            A2D_COLOR_RESET;
#else
        std::cout << A2D_COLOR_INFO
                  << "[" << activeName << ": INFORMATION] " << message
                  << A2D_COLOR_RESET <<  std::endl;
#endif
    }
    if(activeMode > MODE::A2D_CONSOLE_ONLY && fout.is_open()){
        fout << "[" << activeName << ": INFORMATION] " << message << std::endl;
        fout.flush();
    }

}

void A2D::Log::warn(const std::string &message) {
    if(activeMode == MODE::A2D_CONSOLE_ONLY || activeMode == MODE::A2D_ALL) {
#if defined(Windows)
        std::cout << A2D_COLOR_WARNING << "\b"
                << "[" << activeName << ": WARNING] " << message
                << std::endl;
        A2D_COLOR_RESET;
#else
        std::cout << A2D_COLOR_WARNING
                  << "[" << activeName << ": WARNING] " << message
                  << A2D_COLOR_RESET <<  std::endl;
#endif
    }
    if(activeMode > MODE::A2D_CONSOLE_ONLY && fout.is_open()){
        fout << "[" << activeName << ": WARNING] " << message << std::endl;
        fout.flush();
    }
}

void A2D::Log::err(const std::string &message) {
    if(activeMode == MODE::A2D_CONSOLE_ONLY || activeMode == MODE::A2D_ALL) {
#if defined(Windows)
        std::cout << A2D_COLOR_ERROR << "\b"
                << "[" << activeName << ": ERROR] " << message
                << std::endl;
        A2D_COLOR_RESET;
#else
        std::cout << A2D_COLOR_ERROR
                  << "[" << activeName << ": ERROR] " << message
                  << A2D_COLOR_RESET <<  std::endl;
#endif
    }
    if(activeMode > MODE::A2D_CONSOLE_ONLY && fout.is_open()){
        fout << "[" << activeName << ": ERROR] " << message << std::endl;
        fout.flush();
    }
}

void A2D::Log::end() {
    log(SEVERITY::A2D_INFORMATION, "<<< LOG ENDED >>>");
    fout.close();
    init = false;
}

bool A2D::Log::getInit() {
    return init;
}
