#include "acrylic_plexiRenderer_core.hpp"

#include <iostream>


int main(){
    Plexi::initPlexi();

//    std::cin.get();
    Plexi::cleanupPlexi();

//    Plexi::Shader shader = {};
//    Plexi::Shaders::checkForPrecompiledShaders("vert", shader);
//
//
//    std::cout << std::endl;
//
//    Plexi::Shaders::checkForPrecompiledShaders("frag", shader);
//
//    Plexi::Shaders::checkForPrecompiledShaders("notFound", shader);

    return 0;
}