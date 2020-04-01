//
// Created by Corbin Estes on 3/11/20.
//

#include "GLFWBackend.h"


void GLFWBackend::setOnKey(std::function<void (GLFWwindow*, int, int, int, int)> keyCallback) {
    glfwSetKeyCallback(Plexi::getWindowRef(), keyCallback);
}

void GLFWBackend::setOnMouseButton(std::function<void (GLFWwindow *, int, int, int)> mouseCallback){
    glfwSetMouseButtonCallback(Plexi::getWindowRef(), mouseCallback);
}

void GLFWBackend::setOnMouseMove(std::function<void (GLFWwindow *, double, double)> cursorCallback)  {
    glfwSetCursorPosCallback(Plexi::getWindowRef(), cursorCallback);
}

void GLFWBackend::addToKeyMap(int key, int mod, int act, KeyMod A2D) {
    KeyTriple triple = KeyTriple(key, mod, act);
    modMap.insert(std::pair(triple, A2D));
}

KeyMod GLFWBackend::convertKeyToA2DCode(int key, int mod, int act) {
    KeyTriple triple = KeyTriple(key, mod, act);
    return modMap.at(triple);
}