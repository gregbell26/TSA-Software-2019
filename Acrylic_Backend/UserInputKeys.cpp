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
    void (func*);
};

std::vector<keyInfo> keys;

void addKeyMap(int key, int action, void (*func)){
    keys.push_back({key, action, func});
}

static void callback(GLFWwindow* window, int key, int scanCode, int action, int mods){
    int count = 0;
    for (int i = 0; i < keys.size(); ++i) {
        if (keys.at(i).key == key){
            *keys.at(i).func;
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