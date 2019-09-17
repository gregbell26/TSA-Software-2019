//Test file for vulkan
//This code is not for production
#include "vulkan.h"

int main(){
    Vulkan vulkan;

    try {
        vulkan.run();
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}