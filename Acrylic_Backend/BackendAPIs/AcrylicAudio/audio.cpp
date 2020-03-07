#include "audio.hpp"


void tst() {
    ALCdevice* device;
    device = alcOpenDevice(nullptr);
    if(!device){
        std::cout << "Shit" << std::endl;
    } else {
        std::cout << "YEE!" << std::endl;
    }

    alcCloseDevice(device);

}
