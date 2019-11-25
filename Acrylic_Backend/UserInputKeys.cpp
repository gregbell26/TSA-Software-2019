//
// Created by Corbin Estes on 11/20/19.
//
#include <iostream>
#include <GLFW/glfw3.h>
#include <map>
#include "acrylic_engine.hpp"

std::map<std::string, int> key_codes;
std::map<int, void (*)(int)> key_bindings;



void initializeKeys(){
    glfwSetKeyCallback(Plexi::getWindowPtr<GLFWwindow>());
    key_codes.insert(std::pair<std::string, int>("w", glfwGetKeyScancode(GLFW_KEY_W)));
    key_codes.insert(std::pair<std::string, int>("a", glfwGetKeyScancode(GLFW_KEY_A)));
    key_codes.insert(std::pair<std::string, int>("s", glfwGetKeyScancode(GLFW_KEY_S)));
    key_codes.insert(std::pair<std::string, int>("d", glfwGetKeyScancode(GLFW_KEY_D)));
    key_codes.insert(std::pair<std::string, int>("space", glfwGetKeyScancode(GLFW_KEY_SPACE)));
    key_codes.insert(std::pair<std::string, int>("right arrow", glfwGetKeyScancode(GLFW_KEY_RIGHT)));
    key_codes.insert(std::pair<std::string, int>("left arrow", glfwGetKeyScancode(GLFW_KEY_LEFT)));
    key_codes.insert(std::pair<std::string, int>("up arrow", glfwGetKeyScancode(GLFW_KEY_UP)));
    key_codes.insert(std::pair<std::string, int>("down arrow", glfwGetKeyScancode(GLFW_KEY_DOWN)));
    key_codes.insert(std::pair<std::string, int>("left shift", glfwGetKeyScancode(GLFW_KEY_LEFT_SHIFT)));
    key_codes.insert(std::pair<std::string, int>("right shift", glfwGetKeyScancode(GLFW_KEY_RIGHT_SHIFT)));
}

void bindKey(std::string keyName, void (*func)(int)){

}