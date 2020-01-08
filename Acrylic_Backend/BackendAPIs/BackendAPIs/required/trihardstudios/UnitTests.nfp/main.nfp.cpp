#include "../include/ths/log.hpp"

int main(){
    initLogger("Test", severity_information, mode_all)
    logInformation("Yee!")
    logWarning("Yee?")
    logError("Yee!?!?!?!")
    endLogger()


    return 0;
}