#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "UserInput.cpp"
#include <iostream>

static float red = 0.0f;
static float blue = 0.0f;
static float green = 0.0f;
static bool usingRed = true;
UserInput::Returns doTheThing(int times){
    float t = (float)times/100;
    if(usingRed){
        red += t;
        blue -= t;
        if(blue <= 0.0f)
            blue = 0.0f;
    } else {
        blue += t;
        red -= t;
        if(red <= 0.0f)
            red = 0.0f;
    }
    if(red >= 1.0f){
//        red = 0.0f;
        usingRed = false;
    } else if(blue >= 1.0f){
//        blue = 0.0f;
        usingRed = true;
    }
    Plexi::setClearColor(red, 0.0f, blue, 1.0f);

    Plexi::onUpdate();
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
