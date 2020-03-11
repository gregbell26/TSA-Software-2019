//
// Created by Corbin Estes on 3/5/20.
//
#include "KeyInput.hpp"

template <typename T>
std::map<KeyMod, std::function<T>> keyList;

void help(){

}

template <typename T>
Keyboard<T>::Keyboard() {
    keyList<void()>.insert(std::pair<KeyMod, std::function<void()>>(KeyMod(A2D_h, A2D_MOD_NONE), help));
}
template <typename T>
Keyboard<T>::Keyboard(std::map<KeyMod, std::function<T>> keyList){
    keys = keyList;

}

template <typename T>
void Keyboard<T>::check(KeyMod key){
    keys.at(key);
}

template <typename T>
void Keyboard<T>::addKeyBinding(KeyMod key, std::function<T> action){
    keys.insert(std::pair(key, action));
}

