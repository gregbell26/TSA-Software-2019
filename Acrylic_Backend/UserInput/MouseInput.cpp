//
// Created by Corbin Estes on 1/17/20.
//

#include "Input.hpp"
#include "KeyInput.hpp"


#include "MouseInput.hpp"

//#include "Input.cpp"

#include "MouseInput.hpp"
namespace Inputs::Mouse{
    GLFWwindow* getWindowRef(GLFWwindow* window, int act){
        return window;
    }
    template<> MouseInput<GLFWwindow *>::MouseInput(std::vector<MouseInput<GLFWwindow *>> *list){
        key = {0, 0};
        action = getWindowRef;
        list->push_back(*this);
    }
    template<> MouseInput<GLFWwindow*>::MouseInput(int key, std::vector<MouseInput<GLFWwindow *>> *list){
        MouseInput::key = {key, 0};
        action = getWindowRef;
        list->push_back(*this);
    }
    template<> MouseInput<GLFWwindow*>::MouseInput(int key, int modifiers, std::vector<MouseInput<GLFWwindow *>> *list){
        MouseInput::key = {key, modifiers};
        action = getWindowRef;
        list->push_back(*this);
    }
    template <class R>
    MouseInput<R>::MouseInput(int key, std::function<R(GLFWwindow *, int)> action, std::vector<MouseInput<R>> *list){
        MouseInput::key = {key, 0};
        MouseInput::action = action;
        list->push_back(*this);
    }
    template <class R>
    MouseInput<R>::MouseInput(int key, int modifiers, std::function<R(GLFWwindow *, int)> action, std::vector<MouseInput<R>> *list){
        MouseInput::key = {key, modifiers};
        MouseInput::action = action;
        list->push_back(*this);
    }

//    template <class R>
//    std::function<R(GLFWwindow *, int)> MouseInput<R>::getAction() const {
//        return action;
//    }

    template<class R>
    void MouseInput<R>::setAction(R (*func)(GLFWwindow *, int)) {
        MouseInput::action = func;
    }

    template<class R>
    InputType MouseInput<R>::getType(){
        return InputType::mouseButton;
    }

    void logPosition(GLFWwindow* window, double xOff, double yOff){
        double xPos;
        double yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        std::string x = "X: " + std::to_string(xPos);
        std::string y = "Y: " + std::to_string(yPos);

        logInformation(x)
        logInformation(y)
    }
    template<> CursorInput<void>::CursorInput(std::vector<CursorInput<void>> *list){
        action = logPosition;
        list->push_back(*this);
    }
    template <class R>
    CursorInput<R>::CursorInput(std::function<R (GLFWwindow *, double, double)> action, std::vector<CursorInput<R>> *list){
        CursorInput::action = action;
        list->push_back(*this);
    }

//    template <class R>
//    std::function<R(GLFWwindow *, double, double)> CursorInput<R>::getAction() const {
//        return action;
//    }

    template<class R>
    void CursorInput<R>::setAction(std::function<R (GLFWwindow *, double, double)> func) {
        CursorInput::action = func;
    }

    template<class R>
    InputType CursorInput<R>::getType(){
        return InputType::cursorMove;
    }
}