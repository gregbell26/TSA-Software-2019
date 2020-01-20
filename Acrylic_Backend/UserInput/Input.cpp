//
// Created by Corbin Estes on 1/17/20.
//
#include "Input.hpp"
namespace Inputs{

    GLFWwindow* getWindowRef(GLFWwindow* window){
        return window;
    }
    template <>Input<GLFWwindow *>::Input(){
        Input::key = {0, 0};
        Input::action = getWindowRef;
        type = none;
    }
    template <>Input<GLFWwindow *>::Input(std::vector<Input<GLFWwindow *>> *list, InputType type){
        Input::key = {0, 0};
        Input::action = getWindowRef;
        list->push_back(*this);
        Input::type = type;
    }
    template <>Input<GLFWwindow *>::Input(int key, std::vector<Input<GLFWwindow *>> *list, InputType type){
        Input::key = {key, 0};
        Input::action = getWindowRef;
        list->push_back(*this);
        Input::type = type;
    }
    template <>Input<GLFWwindow*>::Input(int key, int modifiers, std::vector<Input<GLFWwindow*>> *list, InputType type){
        Input::key = {key, modifiers};
        Input::action = getWindowRef;
        list->push_back(*this);
        Input::type = type;
    }
    template <class R>
    Input<R>::Input(int key, R (*action)(GLFWwindow *), std::vector<Input<R>> *list, InputType type){
        Input::key = {key, 0};
        Input::action = action;
        list->push_back(*this);
        Input::type = type;
    }
    template <class R>
    Input<R>::Input(int key, int modifiers, R (*action)(GLFWwindow *), std::vector<Input<R>> *list, InputType type){
        Input::key = {key, modifiers};
        Input::action = action;
        list->push_back(*this);
        Input::type = type;
    }

    template<class R>
    void Input<R>::setKey(const Trigger &key) {
        Input::key = key;
    }
    template<class R>
    void Input<R>::setAction(R (*func)(GLFWwindow *)) {
        Input::action = func;
    }

    template<class R>
    const Trigger &Input<R>::getKey() const {
        return key;
    }
    template<class R>
    std::function<R(GLFWwindow *)> Input<R>::getAction() const {
        return action;
    }

    template<class R>
    InputType Input<R>::getType(){
        return type;
    }
}
