//
// Created by Corbin Estes on 1/17/20.
//

#include "Input.hpp"
#include "MouseInput.hpp"
#include "KeyInput.hpp"

namespace Inputs::Key{
    GLFWwindow* getWindowRef(GLFWwindow* window, int act){
        return window;
    }
    template<> KeyInput<GLFWwindow*>::KeyInput(std::vector<KeyInput<GLFWwindow *>> *list){
        key = {0, 0};
        action = getWindowRef;
        list->push_back(*this);
    }
    template<> KeyInput<GLFWwindow*>::KeyInput(int key, std::vector<KeyInput<GLFWwindow *>> *list){
        KeyInput::key = {key, 0};
        action = getWindowRef;
        list->push_back(*this);
    }
    template<> KeyInput<GLFWwindow*>::KeyInput(int key, int modifiers, std::vector<KeyInput<GLFWwindow *>> *list){
        KeyInput::key = {key, modifiers};
        action = getWindowRef;
        list->push_back(*this);
    }
    template <class R>
    KeyInput<R>::KeyInput(int key, R (*action)(GLFWwindow *, int), std::vector<KeyInput<R>> *list){
        KeyInput::key = {key, 0};
        KeyInput::action = action;
        list->push_back(*this);
    }
    template <class R>
    KeyInput<R>::KeyInput(int key, int modifiers, R (*action)(GLFWwindow *, int), std::vector<KeyInput<R>> *list){
        KeyInput::key = {key, modifiers};
        KeyInput::action = action;
        list->push_back(*this);
    }

//    template<class R>
//    std::function<R(GLFWwindow *, int)> KeyInput<R>::getAction() const {
//        return action;
//    }

    template<class R>
    void KeyInput<R>::setAction(R (*func)(GLFWwindow *, int)) {
        KeyInput::action = func;
    }

    template<class R>
    InputType KeyInput<R>::getType(){
        return InputType::keyPress;
    }
}