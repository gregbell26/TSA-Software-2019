//
// Created by Corbin Estes on 3/5/20.
//
#include "MouseInput.hpp"

template <typename T>
std::map<int, std::function<T>> keyList;

void help() {

}

template <typename T>
Mouse<T>::Mouse() {
    keyList<void()>.insert(std::pair<MouseButtons , std::function<void()>>(A2D_MOUSE_BUTTON_LEFT, help));
}
template <typename T>
Mouse<T>::Mouse(std::map<MouseButtons, std::function<T>> keyList){
    buttons = keyList;
}

template <typename T>
void Mouse<T>::check(int buttonPress){
    buttons.at(buttonPress);
}

template <typename T>
void Mouse<T>::addButtonBinding(MouseButtons button, std::function<T> action){
    buttons.insert(std::pair(button, action));
}

template <typename T>
T Mouse<T>::cursorMove(A2D_coordPair coord){
    return cursorFunction(coord);
}

template <typename T>
void Mouse<T>::setCursorFunction(std::function<T(A2D_coordPair)> action){
    cursorFunction = action;
}


