#ifndef A2D_LOG_HPP
#define A2D_LOG_HPP


#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace A2D {
    class Log {
    public:
        enum class SEVERITY {
            A2D_INFORMATION = 0,
            A2D_WARNING,
            A2D_ERROR,

        };

        enum class MODE {
            A2D_CONSOLE_ONLY = 0,
            A2D_FILE_ONLY,
            A2D_ALL

        };
//protected:
//    enum class PLATFORM {
//        WINDOWS = 0,
//        MACOS,
//        LINUX,
//    };

    public:

        static void initLog(const char *name, SEVERITY severity, MODE mode);

        static void log(SEVERITY severity, const std::string &message);

        static void end();

    private:
        static void info(const std::string &message);

        static void warn(const std::string &message);

        static void err(const std::string &message);

    };

}

#define severity_information A2D::Log::SEVERITY::A2D_INFORMATION
#define severity_warning A2D::Log::SEVERITY::A2D_WARNING
#define severity_error A2D::Log::SEVERITY::A2D_ERROR

#define mode_console A2D::Log::MODE::A2D_CONSOLE_ONLY
#define mode_file A2D::Log::MODE::A2D_FILE_ONLY
#define mode_all A2D::Log::MODE::A2D_ALL

#define initLogger(name, severity, mode) A2D::Log::initLog(name, severity, mode);
#define endLogger() A2D::Log::end();

#define logInformation(message) A2D::Log::log(severity_information, message);
#define logWarning(message) A2D::Log::log(severity_warning, message);
#define logError(message) A2D::Log::log(severity_error, message);


#endif //A2D_LOG_HPP
