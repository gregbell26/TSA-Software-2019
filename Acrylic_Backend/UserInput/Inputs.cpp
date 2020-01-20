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

    //Key Callback
    //Runs through all key activated inputs and runs them if they match the pressed key
    template <typename T>
    T runKey(GLFWwindow* window, int key, int scancode, int action, int mods){
        for (int i = 0; i< inputList<T>.size(); i++){
            if (keyInputList<T>.at(i).getType() == keyPress){
                Key::KeyInput<T> element = keyInputList<T>.at(i);
                if (element.key.key == key){
                    if (element.key.modifiers == mods){
                        return element.action(window, action);
                    }
                }
            }
            if (inputList<T>.at(i).getType() == keyPress){
                Input<T> element = inputList<T>.at(i);
                if (element.key.key == key){
                    if (element.key.modifiers == mods){
                        return element.action(window);
                    }
                }
            }
        }
    }

    //Mouse Button Callback
    //Runs through all mouse activated inputs and runs them if they match the pressed button
    template <typename T>
    T runMouseButton(GLFWwindow* window, int button, int action, int mods){
        for (int i = 0; i<inputList<T>.size(); i++){
            if (mouseInputList<T>.at(i).getType() == mouseButton){
                Mouse::MouseInput<T> element = mouseInputList<T>.at(i);
                if (element.key.key == button){
                    if (element.key.modifiers == mods){
                        return element.action(window, action);
                    }
                }
            }
            if (inputList<T>.at(i).getType() == mouseButton){
                Input<T> element = inputList<T>.at(i);
                if (element.key.key == button){
                    if (element.key.modifiers == mods){
                        return element.action(window);
                    }
                }
            }
        }
    }

    //Cursor Move
    //Runs all cursor and scroll activated functions
    template <typename T>
    T runCursorMove(GLFWwindow* window, double xPos, double yPos){
        for (int i = 0; i<inputList<T>.size(); i++){
            if (cursorInputList<T>.at(i).getType() == cursorMove){
                Mouse::CursorInput<T> element = cursorInputList<T>.at(i);
                return element.action(window, xPos, yPos);
            }
            if (inputList<T>.at(i).getType() == cursorMove){
                Input<T> element = inputList<T>.at(i);
                return element.action(window);
            }
        }
    }

    //Sets callbacks
    void init(){
        glfwSetKeyCallback(Plexi::getWindowRef(), runKey);
        glfwSetMouseButtonCallback(Plexi::getWindowRef(), runMouseButton);
        glfwSetCursorPosCallback(Plexi::getWindowRef(), runCursorMove);
    }

    //Input constructors
    Input<GLFWwindow *> newInput(InputType type){
        std::vector<Input<GLFWwindow*>> *list = &inputList<GLFWwindow*>;
        return Input<GLFWwindow*>(list, type);
    }
    Input<GLFWwindow *> newInput(int key, InputType type){
        std::vector<Input<GLFWwindow*>> *list = &inputList<GLFWwindow*>;
        return Input<GLFWwindow*>(key, list, type);
    }
    Input<GLFWwindow*> newInput(int key, int modifiers, InputType type){
        std::vector<Input<GLFWwindow*>> *list = &inputList<GLFWwindow*>;
        return Input<GLFWwindow*>(key, modifiers, list, type);
    }
    template <class R>
    Input<R> newInput(int key, R (*action)(GLFWwindow *), InputType type){
        std::vector<Input<R>> *list = &inputList<R>;
        return Input<R>(key, action, list, type);
    }
    template <class R>
    Input<R> newInput(int key, int modifiers, R (*action)(GLFWwindow *), InputType type){
        std::vector<Input<R>> *list = &inputList<R>;
        return Input<R>(key, modifiers, action, list, type);
    }

    //KeyInput constructors
    Key::KeyInput<GLFWwindow*> newKeyInput(){
        std::vector<Key::KeyInput<GLFWwindow*>> *list = &keyInputList<GLFWwindow*>;
        return Key::KeyInput<GLFWwindow*>(list);
    }
    Key::KeyInput<GLFWwindow*> newKeyInput(int key){
        std::vector<Key::KeyInput<GLFWwindow*>> *list = &keyInputList<GLFWwindow*>;
        return Key::KeyInput<GLFWwindow*>(key, list);
    }
    Key::KeyInput<GLFWwindow*> newKeyInput(int key, int modifiers){
        std::vector<Key::KeyInput<GLFWwindow*>> *list = &keyInputList<GLFWwindow*>;
        return Key::KeyInput<GLFWwindow*>(key, modifiers, list);
    }
    template <class R>
    Key::KeyInput<R> newKeyInput(int key, R (*action)(GLFWwindow *, int)){
        std::vector<Key::KeyInput<R>> *list = &keyInputList<R>;
        return Key::KeyInput<R>(key, action, list);
    }
    template <class R>
    Key::KeyInput<R> newKeyInput(int key, int modifiers, R (*action)(GLFWwindow *, int)){
        std::vector<Key::KeyInput<R>> *list = &keyInputList<R>;
        return Key::KeyInput<R>(key, modifiers, action, list);
    }

    //MouseButtonInput constructors
    Mouse::MouseInput<GLFWwindow *> newMouseInput(){
        std::vector<Mouse::MouseInput<GLFWwindow*>> *list = &mouseInputList<GLFWwindow*>;
        return Mouse::MouseInput<GLFWwindow*>(list);
    }
    Mouse::MouseInput<GLFWwindow*> newMouseInput(int key){
        std::vector<Mouse::MouseInput<GLFWwindow*>> *list = &mouseInputList<GLFWwindow*>;
        return Mouse::MouseInput<GLFWwindow*>(key, list);
    }
    Mouse::MouseInput<GLFWwindow*> newMouseInput(int key, int modifiers){
        std::vector<Mouse::MouseInput<GLFWwindow*>> *list = &mouseInputList<GLFWwindow*>;
        return Mouse::MouseInput<GLFWwindow*>(key, modifiers, list);
    }
    template <class R>
    Mouse::MouseInput<R> newMouseInput(int key, R (*action)(GLFWwindow *, int)){
        std::vector<Mouse::MouseInput<R>> *list = &mouseInputList<R>;
        return Mouse::MouseInput<R>(key, action, list);
    }
    template <class R>
    Mouse::MouseInput<R> newMouseInput(int key, int modifiers, R (*action)(GLFWwindow *, int)){
        std::vector<Mouse::MouseInput<R>> *list = &mouseInputList<R>;
        return Mouse::MouseInput<R>(key, modifiers, action, list);
    }

    //CursorMoveInput constructors
    Mouse::CursorInput<void> newCursorInput(){
        std::vector<Mouse::CursorInput<void>> *list = &cursorInputList<void>;
        return Mouse::CursorInput<void>(list);
    }
    template <class R>
    Mouse::CursorInput<R> newCursorInput(R (*action)(GLFWwindow *, double, double)){
        std::vector<Mouse::CursorInput<R>> *list = &cursorInputList<R>;
        return Mouse::CursorInput<R>(action, list);
    }
}