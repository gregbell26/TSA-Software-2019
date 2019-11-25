#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "UserInputKeys.cpp"

void doTheThing(int times){
    std::cout << "hi: " << times<< std::endl;
}

int main(){
    Plexi::initPlexi();
    readJSON('a');
    addKeyMap(27, 82, doTheThing);
}
