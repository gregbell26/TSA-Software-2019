#include "acrylic_plexiRenderer_core.hpp"

#include <iostream>

int main(){
    Plexi::initPlexi();

    std::cin.get();
    Plexi::cleanupPlexi();
    return 0;
}