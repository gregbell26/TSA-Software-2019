#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "UserInputKeys.cpp"
#include <iostream>
void doTheThing(int times){
    std::cout << "hi: " << times<< std::endl;
}

int main(){
    Plexi::initPlexi();
    initialize();
    addKeyMap(GLFW_KEY_W, GLFW_PRESS, doTheThing);
    addKeyMap(GLFW_KEY_A, GLFW_PRESS, nullptr);
    addKeyMap(GLFW_KEY_S, GLFW_PRESS, doTheThing);
    addKeyMap(GLFW_KEY_D, GLFW_PRESS, doTheThing);
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
    }
    Plexi::cleanupPlexi();
//    readJSON('a');
}
