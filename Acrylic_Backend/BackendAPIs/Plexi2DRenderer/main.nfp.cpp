#include "acrylic_plexiRenderer_core.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

int main(){
    Plexi::initPlexi();

    //std::cin.get();
    Plexi::cleanupPlexi();
    return 0;
}