#include "./BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
#include "./BackendAPIs/AcrylicSaveEngine/FileSystemBackend/acrylic_fileSystem.hpp"
#include "UserInput.cpp"
#include <iostream>

static float red = 0.0f;
static float blue = 0.0f;
static float green = 0.0f;
static bool usingRed = true;
UserInput::Returns doTheThing(int times){
    float t = (float)times/10;
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

    return {};
}

UserInput::Returns scroll(double i, double j){
    j = abs(j);
    float t = (float)(j)/1000;
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
    return {};
}
int main(){
    Plexi::initPlexi();
    UserInput::initialize();
    UserInput::addKeyMap(GLFW_KEY_W, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_A, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_S, GLFW_PRESS, doTheThing);
    UserInput::addKeyMap(GLFW_KEY_D, GLFW_PRESS, doTheThing);
    UserInput::setCursorPressedMoveFunc(scroll);
    UserInput::setScrollFunc(scroll);
    UserInput::setMouseRightFunc(GLFW_MOUSE_BUTTON_LEFT, doTheThing);
    Plexi::setClearColor(0.1f,0.1f,0.1f,1.0f);
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::onUpdate();
    }
    Plexi::cleanupPlexi();
//    readJSON('a');
}
