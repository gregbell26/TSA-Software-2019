//
// Created by Corbin Estes on 3/5/20.
//
#include "MouseInput.hpp"

template <typename T>
std::map<int, std::function<T>> keyList;

void help() {

}

template <typename B, typename C>
Mouse<B, C>::Mouse() {
    keyList<void()>.insert(std::pair<MouseButtons , std::function<void()>>(A2D_MOUSE_BUTTON_LEFT, help));
}
template <typename B, typename C>
Mouse<B, C>::Mouse(std::map<MouseButtons, std::function<B>> buttonList){
    buttons = buttonList;
}

template <typename B, typename C>
void Mouse<B, C>::check(int buttonPress){
    buttons.at(buttonPress);
}

template <typename B, typename C>
void Mouse<B, C>::addButtonBinding(MouseButtons button, std::function<B> action){
    buttons.insert(std::pair(button, action));
}

template <typename B, typename C>
C Mouse<B, C>::cursorMove(A2D_coordPair coord){
    return cursorFunction(coord);
}

template <typename B, typename C>
void Mouse<B, C>::setCursorFunction(std::function<C> action){
    cursorFunction = action;
}

template <typename B, typename C>
void Mouse<B, C>::removeButtonBinding(MouseButtons button) {
    buttons.erase(button);
}