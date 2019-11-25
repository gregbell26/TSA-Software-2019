//
// Created by Corbin Estes on 11/20/19.
//
#include <iostream>
#include <GLFW/glfw3.h>
#include "BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"
//TODO add cursor move and exit events and parameter list
namespace UserInput{
    union Returns{
        char str[100];
        int integer;
        float decimal;
        double Double;
        char character;
    };

    struct keyInfo {
        int key;
        int action;
        Returns (*func)(int);
    };

    std::vector<keyInfo> keys;
    Returns (*mouseButtonFunctions[8])(int);
    Returns (*scrollFunc)(double, double);

    void changeKeyMap(int key, int action, Returns (*func)(int)){
        for (auto & i : keys) {
            i = keyInfo{key, action, func};
        }
    }

    void addKeyMap(int key, int action, Returns (*func)(int)){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            keys.push_back(keyInfo{key, action, func});
        }
    }

    void setMouseRightFunc(int index, Returns (*func)(int)){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            mouseButtonFunctions[index] = func;
        }
    }

    void setScrollFunc(Returns (*func)(double, double)){
        if (func == nullptr){
            std::cout << "Invalid input function" << std::endl;
        } else {
            scrollFunc = func;
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
        mouseButtonFunctions[button];
    }

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
        scrollFunc(xoffset, yoffset);
    }

    void initialize(){
        glfwSetKeyCallback(Plexi::getWindowRef(), keyCallback);
        glfwSetMouseButtonCallback(Plexi::getWindowRef(), mouseButtonCallback);
        glfwSetScrollCallback(Plexi::getWindowRef(), scrollCallback);
    }
}