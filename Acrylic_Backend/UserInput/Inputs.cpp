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
    std::vector<Key::KeyInput<T>> keyInputList;
    template <typename T>
    std::vector<Mouse::MouseInput<T>> mouseInputList;
    template <typename T>
    std::vector<Mouse::CursorInput<T>> cursorInputList;
    template <typename T>
    T runKey(GLFWwindow* window, int key, int scancode, int action, int mods){
        for (int i = 0; i< inputList<T>.size(); i++){
            if (keyInputList<T>.at(i).getType() == keyPress){
                Key::KeyInput<T> element = keyInputList<T>.at(i);
                if (element.key.key == key){
                    if (element.key.modifiers == mods){
                        return element.action(Plexi::getWindowRef(), action);
                    }
                }
            }
            if (inputList<T>.at(i).getType() == keyPress){
                Input<T> element = inputList<T>.at(i);
                if (element.key.key == key){
                    if (element.key.modifiers == mods){
                        return element.action(Plexi::getWindowRef());
                    }
                }
            }
        }
    }

    template <typename T>
    T runMouseButton(GLFWwindow* window, int button, int action, int mods){
        for (int i = 0; i<inputList<T>.size(); i++){
            if (mouseInputList<T>.at(i).getType() == mouseButton){
                Mouse::MouseInput<T> element = mouseInputList<T>.at(i);
                if (element.key.key == button){
                    if (element.key.modifiers == mods){
                        return element.action(Plexi::getWindowRef(), action);
                    }
                }
            }
            if (inputList<T>.at(i).getType() == mouseButton){
                Input<T> element = inputList<T>.at(i);
                if (element.key.key == button){
                    if (element.key.modifiers == mods){
                        return element.action(Plexi::getWindowRef());
                    }
                }
            }
        }
    }

    template <typename T>
    T runCursorMove(GLFWwindow* window, double xPos, double yPos){
        for (int i = 0; i<inputList<T>.size(); i++){
            if (cursorInputList<T>.at(i).getType() == cursorMove){
                Mouse::CursorInput<T> element = cursorInputList<T>.at(i);
                return element.action(Plexi::getWindowRef(), xPos, yPos);
            }
            if (inputList<T>.at(i).getType() == cursorMove){
                Input<T> element = inputList<T>.at(i);
                return element.action(Plexi::getWindowRef());
            }
        }
    }

    void init(){
        glfwSetKeyCallback(Plexi::getWindowRef(), runKey);
        glfwSetMouseButtonCallback(Plexi::getWindowRef(), runMouseButton);
        glfwSetCursorPosCallback(Plexi::getWindowRef(), runCursorMove);
    }
}