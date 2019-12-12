//
// Created by Corbin Estes on 11/20/19.
//
#include "UserInput.hpp"
namespace UserInput{
    void changeKeyMap(int key, int action, Returns (*func)(int action)){
        for (auto & i : keys) {
            i = keyInfo{key, action, func};
        }
    }

    void addKeyMap(int key, int action, Returns (*func)(int action)){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            keys.push_back(keyInfo{key, action, func});
        }
    }

    void setMouseRightFunc(int index, Returns (*func)(int action)){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            mouseButtonFunctions[index] = func;
        }
    }

    void setScrollFunc(Returns (*func)(double xoffset, double yoffset)){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            scrollFunc = func;
        }
    }

    void setWindowEnterFunc(Returns (*func)()){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            enterWindowFunc = func;
        }
    }

    void setWindowExitFunc(Returns (*func)()){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            exitWindowFunc = func;
        }
    }

    static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods){
        int count = 0;
        for (auto & i : keys) {
            if (i.key == key){
                i.func(action);
                count++;
            }
        }
        if (count == 0){
            //TODO Use logger instead of cout
            std::cout << "Keymap doesn't exist" << std::endl;
        }
    }

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
        if(mouseButtonFunctions[button] != nullptr)
            mouseButtonFunctions[button](action);
    }

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
        if(scrollFunc != nullptr)
            scrollFunc(xoffset, yoffset);
    }

    static void cursorEnterCallback(GLFWwindow* window, int entered){
        if (entered){
            if(enterWindowFunc != nullptr)
                enterWindowFunc();
        }
        else{
            if(exitWindowFunc != nullptr)
                exitWindowFunc();
        }
    }

    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS) {
            cursorPressedMoveFunc(xpos, ypos);
        } else {
            if(cursorMoveFunc != nullptr)
                cursorMoveFunc(xpos, ypos);
        }
    }

    void initialize(){
        glfwSetKeyCallback(Plexi::getWindowRef(), keyCallback);
        glfwSetMouseButtonCallback(Plexi::getWindowRef(), mouseButtonCallback);
        glfwSetScrollCallback(Plexi::getWindowRef(), scrollCallback);
        glfwSetCursorEnterCallback(Plexi::getWindowRef(), cursorEnterCallback);
        glfwSetCursorPosCallback(Plexi::getWindowRef(), cursorPositionCallback);
    }

    void cursorHiddenToggle(GLFWwindow* window){
        int mode = glfwGetInputMode(window, GLFW_CURSOR);
        if (mode == GLFW_CURSOR_HIDDEN) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
    }

    void cursorDisabledToggle(GLFWwindow* window){
        int mode = glfwGetInputMode(window, GLFW_CURSOR);
        if (mode == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}