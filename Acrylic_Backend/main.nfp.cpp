#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "UserInput.cpp"
#include <iostream>
UserInput::Returns doTheThing(int times){
    Plexi::onUpdate();
    glfwSwapBuffers(Plexi::getWindowRef());
    return {};
}

UserInput::Returns scroll(double i, double j){
    Plexi::onUpdate();
    glfwSwapBuffers(Plexi::getWindowRef());    return {};
}
int main(){
    Plexi::initPlexi();
    UserInput::initialize();
    UserInput::addKeyMap(GLFW_KEY_W, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_A, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_S, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_D, GLFW_PRESS, doTheThing);
    UserInput::setScrollFunc(scroll);
    UserInput::setMouseRightFunc(GLFW_MOUSE_BUTTON_LEFT, doTheThing);
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
    }
    Plexi::cleanupPlexi();
//    readJSON('a');
}
