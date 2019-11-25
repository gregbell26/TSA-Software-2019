//
// Created by Corbin Estes on 11/20/19.
//
#include <iostream>
#include <GLFW/glfw3.h>
#include <map>
#include "BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"

struct keyInfo {
    int key;
    int action;
    void (*func)(int);
};

std::vector<keyInfo> keys;

void addKeyMap(int key, int action, void (*func)(int)){
    keys.push_back(keyInfo{key, action, func});
}

static void callback(GLFWwindow* window, int key, int scanCode, int action, int mods){
    int count = 0;
    for (int i = 0; i < keys.size(); ++i) {
        if (keys.at(i).key == key){
            keys.at(i).func(action);
            count++;
        }
    }
    if (count == 0){
        //TODO Use logger instead of cout
        std::cout << "Keymap doesn't exist" << std::endl;
    }
}

void initialize(){
    glfwSetKeyCallback(Plexi::getWindowRef(), callback);
}