//
// Created by Corbin Estes on 3/5/20.
//
#include "MouseInput.hpp"

template <typename T>
std::map<int, std::function<T>> keyList;

void help(){

}

template <typename T>
Mouse<T>::Mouse() {
    keyList<void()>.insert(std::pair<int, std::function<void()>>(1, help));
}
template <typename T>
Mouse<T>::Mouse(std::map<int, std::function<T>> keyList){
    buttons = keyList;
}

template <typename T>
void Mouse<T>::check(){
    int buttonPress = getchar();
    buttons.at(buttonPress);
}

template <typename T>
void Mouse<T>::addButtonBinding(int button, std::function<T> action){
    buttons.insert(std::pair(button, action));
}

