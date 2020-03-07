//
// Created by Corbin Estes on 3/5/20.
//
#include "KeyInput.hpp"

template <typename T>
std::map<char, std::function<T>> keyList;

void help(){

}

template <typename T>
Keyboard<T>::Keyboard() {
    keyList<void()>.insert(std::pair<char, std::function<void()>>('h', help));
}
template <typename T>
Keyboard<T>::Keyboard(std::map<char, std::function<T>> keyList){
    keys = keyList;
}

template <typename T>
void Keyboard<T>::check(){
    int keyPress = getchar();
    keys.at(keyPress);
}

template <typename T>
void Keyboard<T>::addKeyBinding(char key, std::function<T> action){
    keys.insert(std::pair(key, action));
}

