//
// Created by Corbin Estes on 1/18/20.
//
#include "Input.hpp"
#include "KeyInput.hpp"
#include "MouseInput.hpp"

namespace Inputs {
    template <typename T>
    std::vector<Input<T>> inputList;
    template <typename T>
    T runKey(GLFWwindow* window, int key, int scancode, int action, int mods){
        for (int i = 0; i< inputList<T>.size(); i++){
            if (inputList<T>.at(i).getType() == keyPress){
                Key::KeyInput<T> element = inputList<T>.at(i);
                if (element.key.key == key){
                    if (element.key.modifiers == mods){
                        return element.action(Plexi::getWindowRef(), action);
                    }
                }
            }
        }
    }

    T runMouseButton(GLFWwindow* window, int button, int action, int mods){
        for (int i = 0; i<inputList.size(); i++){
            if (inputList.at(i).getType() == mouseButton){
                Mouse::MouseInput<T> element = inputList.at(i);
                if (element.key.key == button){
                    if (element.key.modifiers == mods){
                        return element.action(Plexi::getWindowRef(), action);
                    }
                }
            }
        }
    }

    T runCursorMove(GLFWwindow* window, double xPos, double yPos){
        for (int i = 0; i<inputList.size(); i++){
            if (inputList.at(i).getType() == cursorMove){
                Mouse::CursorInput<T> element = inputList.at(i);
                return element.action(Plexi::getWindowRef(), xPos, yPos);
            }
        }
    }

    void init(){
        glfwSetKeyCallback(Plexi::getWindowRef(), runKey());
        glfwSetMouseButtonCallback(Plexi::getWindowRef(), runKey());
        glfwSetCursorPosCallback(Plexi::getWindowRef(), runKey());
    }
}