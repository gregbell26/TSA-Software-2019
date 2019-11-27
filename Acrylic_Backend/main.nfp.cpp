#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "UserInput.cpp"
#include <iostream>
UserInput::Returns doTheThing(int times){
    std::cout << "hi: " << times<< std::endl;
    return {};
}

UserInput::Returns scroll(double i, double j){
    std::cout << "Scroll " << i << ", " << j << std::endl;
    return {};
}
int main(){
    Plexi::initPlexi();
    UserInput::initialize();
    UserInput::addKeyMap(GLFW_KEY_W, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_A, GLFW_PRESS, nullptr);
    UserInput::addKeyMap(GLFW_KEY_S, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_D, GLFW_PRESS, doTheThing);
    UserInput::setScrollFunc(scroll);
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
    }
    Plexi::cleanupPlexi();
//    readJSON('a');
}
